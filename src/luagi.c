/*
 * MIT License
 * 
 * Copyright (c) 2016 Johannes Westhuis, Alexander Schulz
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <lua.h>
#include <lauxlib.h>
#include <git2/global.h>
#include <git2/signature.h>   

#include <string.h>
#include <stdio.h>

#include "luagi.h"
#include "repository.h"
#include "common.h"
#include "branch.h"
#include "tree.h"
#include "commit.h"
#include "clone.h"
#include "remote.h"
#include "status.h"
#include "diff.h"
#include "index.h"
#include "object.h"
#include "checkout.h"
#include "stash.h"
#include "reference.h"
#include "merge.h"
#include "blob.h"
#include "cherrypick.h"
#include "reset.h"
#include "revert.h"
#include "tag.h"
#include "submodule.h"
#include "graph.h"
#include "note.h"
#include "blame.h"
#include "ignore.h"
#include "odb.h"
#include "refdb.h"
#include "config.h"
#include "reflog.h"
#include "indexer.h"
#include "patch.h"
#include "pack.h"
#include "revwalk.h"
#include "annotated_commit.h"

static const struct luaL_Reg repofuncs [] = {
   { "branch", luagi_create_branch },
   { "branches", luagi_branches }, 
   { "lookup_branch", luagi_branch_lookup }, 
   { "lookup_commit", luagi_commit_lookup },
   { "lookup_tree", luagi_tree_lookup }, 
   { "commit", luagi_commit_create }, 
   { "clone_into", luagi_clone_into },
   { "__gc", luagi_gc },
   //remotes
   { "remotes", luagi_remote_list },
   { "rename_remote", luagi_remote_rename },
   { "lookup_remote", luagi_remote_lookup },
   { "create_remote", luagi_remote_create },
   { "delete_remote", luagi_remote_delete },
   //status
   { "status_for_each", luagi_status_foreach },
   { "status_for_each_ext", luagi_status_foreach_ext },
   { "status_file", luagi_status_file },
   { "status_list", luagi_status_list_new },
   { "status_ignored", luagi_status_should_ignore },
   //diff

   { "diff_tree_to_index", luagi_diff_tree_to_index },
   { "diff_tree_to_tree", luagi_diff_tree_to_tree },
   { "diff_index_to_workdir", luagi_diff_index_to_workdir },
   { "diff_tree_to_workdir",luagi_diff_tree_to_workdir },
   { "diff_tree_to_workdir_with_index", luagi_diff_tree_to_workdir_with_index },
   { "diff_commit_as_email", luagi_diff_commit_as_email },

   { "index", luagi_repository_index },
   //treeentry
   { "treeentry_to_object", luagi_tree_entry_to_object },
   //checkout
   { "checkout_head", luagi_checkout_head },
   { "checkout_index", luagi_checkout_index },
   { "checkout_tree", luagi_checkout_tree },

   //stash
   { "stash", luagi_stash_save },
   { "stash_for_each", luagi_stash_foreach },
   { "stash_drop", luagi_stash_drop },

   //reference
   { "create_reference", luagi_reference_create },
   { "create_reference_matching", luagi_reference_create_matching },
   { "create_symbolic_reference", luagi_reference_symbolic_create },
   { "create_symbolic_reference_matching", luagi_reference_symbolic_create_matching },
   { "lookup_reference", luagi_reference_lookup },
   { "reference_name_to_id", luagi_reference_name_to_id },
   { "reference_dwim", luagi_reference_dwim },
   { "remove_reference", luagi_reference_remove },
   { "list_references", luagi_reference_list },
   { "foreach_reference", luagi_reference_foreach },
   { "foreach_reference_with_glob", luagi_reference_foreach_glob },
   { "iterate_references", luagi_reference_iterator },
   { "reference_has_log", luagi_reference_has_log },
   { "reference_ensure_log", luagi_reference_ensure_log },
   { "remove_reference", luagi_reference_remove },
   { "list_references", luagi_reference_list },

   //merge
   { "merge_base", luagi_merge_base },
   { "merge_base_many", luagi_merge_base_many },
   { "merge_base_octopus", luagi_merge_base_octopus },
   { "annotated_commit_from_ref", luagi_annotated_commit_from_ref },
   { "annotated_commit_from_fetchhead", luagi_annotated_commit_from_fetchhead },
   { "annotated_commit_lookup", luagi_annotated_commit_lookup },
   { "merge_trees", luagi_merge_trees },
   { "merge_commits", luagi_merge_commits },
   { "merge", luagi_merge },
   { "merge_file_from_index", luagi_merge_file_from_index },
   { "merge_analysis", luagi_merge_analysis },
   // blob
   { "lookup_blob", luagi_blob_lookup },
   { "create_blob_from_workdir", luagi_blob_create_fromworkdir },
   { "create_blob_from_disk", luagi_blob_create_fromdisk },
   { "create_blob_from_buffer", luagi_blob_create_frombuffer },
   // cherrypick
   { "cherrypick", luagi_cherrypick },
   { "cherrypick_commit", luagi_cherrypick_commit },

   //reset
   { "reset", luagi_reset },
   { "reset_default", luagi_reset_default },
   { "reset_index", luagi_reset_index },
   //revert
   { "revert", luagi_revert },
   { "revert_commit", luagi_revert_commit },
   //tag
   { "lookup_tag", luagi_tag_lookup },
   { "create_tag", luagi_tag_create },
   { "create_tag_annotation", luagi_tag_annotation_create },
   //{ "create_tag_from_buffer", luagi_tag_create_frombuffer },
   { "create_tag_lightweight", luagi_tag_create_lightweight },
   { "delete_tag", luagi_tag_delete },

   { "list_tags", luagi_tag_list },
   { "list_tags_matching", luagi_tag_list_match },
   { "foreach_tag", luagi_tag_foreach },

   { "lookup_submodule",  luagi_submodule_lookup },
   { "foreach_submodule", luagi_submodule_foreach },
   { "add_submodule_setup", luagi_submodule_add_setup },
   { "resolve_submodule_url", luagi_submodule_resolve_url },
   { "submodule_repo_init", luagi_submodule_repo_init },

   //graph
   { "graph_ahead_behind", luagi_graph_ahead_behind },
   { "graph_descendant_of", luagi_graph_descendant_of },
   //note
   { "notes", luagi_note_iterator },
   { "foreach_note", luagi_note_foreach },

   { "read_note", luagi_note_read },
   { "create_note", luagi_note_create },
   { "remove_note", luagi_note_remove },
   { "note_default_ref", luagi_note_default_ref },

   { "blame_file", luagi_blame_file },

   { "add_ignore_rules", luagi_ignore_add_rules },
   { "clear_internal_ignore_rules", luagi_ignore_clear_internal_rules },
   { "is_path_ignored", luagi_ignore_path_is_ignored },

   { "head", luagi_repository_head },
   { "is_head_detached", luagi_repository_head_detached },
   { "is_head_unborn", luagi_repository_head_unborn },
   { "is_empty", luagi_repository_is_empty },
   { "is_bare", luagi_repository_is_bare },
   { "is_shallow",luagi_repository_is_shallow },
   { "path", luagi_repository_path },
   { "workdir", luagi_repository_workdir },
   { "set_workdir", luagi_repository_set_workdir },
   { "config",  luagi_repository_config },
   { "config_snapshot", luagi_repository_config_snapshot },
   { "odb", luagi_repository_odb },
   { "refdb", luagi_repository_refdb },
   { "message", luagi_repository_message },
   { "remove_message", luagi_repository_message_remove },
   { "cleanup_state", luagi_repository_state_cleanup },
   { "foreach_fetchhead", luagi_repository_fetchhead_foreach },
   { "foreach_mergehead", luagi_repository_mergehead_foreach },
   { "hashfile", luagi_repository_hashfile },
   { "set_head", luagi_repository_set_head },
   { "set_head_detached", luagi_repository_set_head_detached },
   { "detach_head", luagi_repository_detach_head },
   { "state", luagi_repository_state },
   { "set_namespace", luagi_repository_set_namespace },
   { "get_namespace", luagi_repository_get_namespace },
   //refdb
   { "new_refdb", luagi_refdb_new },
   { "open_refdb", luagi_refdb_open },
   //reflog
   { "read_reflog", luagi_reflog_read },
   { "rename_reflog", luagi_reflog_rename },
   { "delete_reflog", luagi_reflog_delete },
   //pack
   { "new_packbuilder", luagi_packbuilder_new },
   //revwalk
   { "revwalk", luagi_revwalk_new },
   //object
   { "lookup_object", luagi_object_lookup },
   { "lookup_object_bypath", luagi_object_lookup_bypath },
   { "tree_builder", luagi_tree_builder_new },
   //remote
   { "remote_set_autotag",                 luagi_remote_set_autotag             },
   { "remote_set_pushurl",                 luagi_remote_set_pushurl             },
   { "remote_add_fetch",                   luagi_remote_add_fetch               },
   { "remote_add_push",                    luagi_remote_add_push                },
   { "remote_set_url",                     luagi_remote_set_url                 },
   //submodule
   { "submodule_status", luagi_submodule_status },
   { "submodule_set_update", luagi_submodule_set_update },
   { "submodule_set_url", luagi_submodule_set_url },
   { "submodule_set_fetch_recurse", luagi_submodule_set_fetch_recurse_submodules },
   { "submodule_set_ignore", luagi_submodule_set_ignore },
   { NULL, NULL },
};

static const struct luaL_Reg mylib [] = {
   { "version", luagi_version },
   { "features", luagi_features },
   { "open", luagi_open },
   { "clone", luagi_clone },
   // remote
   { "is_valid_remote_name", luagi_remote_is_valid_name   },
   //index if path is given, it does open
   { "create_index", luagi_index_new },
   { "reference_normalize_name", luagi_reference_normalize_name },
   { "reference_is_valid_name", luagi_reference_is_valid_name },
   { "merge_files", luagi_merge_file },
   { "wrap_odb", luagi_repository_wrap_odb },
   { "discover", luagi_repository_discover },
   { "open_ext", luagi_repository_open_ext },
   { "open_bare",luagi_repository_open_bare },
   { "init", luagi_repository_init },
   { "init_ext",luagi_repository_init_ext },
   { "new_odb", luagi_odb_new },
   { "open_odb", luagi_odb_open },

   { "hash", luagi_odb_hash },
   { "hashfile", luagi_odb_hashfile },
   //config
   { "find_global_config", luagi_config_find_global },
   { "find_xdg_config", luagi_config_find_xdg },
   { "find_system_config", luagi_config_find_system },

   { "open_default_config", luagi_config_open_default },
   { "new_config", luagi_config_new },
   { "open_ondisk_config", luagi_config_open_ondisk },

   { "parse_bool", luagi_config_parse_bool },
   { "parse_int32", luagi_config_parse_int32 },
   { "parse_int64", luagi_config_parse_int64 },

   { "patch_buffers", luagi_patch_from_buffers },
   { NULL, NULL } /*sentinel*/
};

void setup_funcs( lua_State *L, const char *meta_name, const luaL_Reg *funcs )
{
   luaL_newmetatable( L, meta_name );
   lua_pushvalue( L, -1 );
   lua_setfield( L, -2, "__index");
   luaL_setfuncs( L, funcs, 0);
}
int luaopen_luagi(lua_State *L)
{
   git_libgit2_init();
   /* metatable for the branch iterator */
   luaL_newmetatable( L, LUAGI_BRANCH_STATICS );
   lua_pushcfunction( L, luagi_branch_iter_gc);
   lua_setfield( L, -2, "__gc" );

   luaL_newmetatable( L, LUAGI_NOTE_ITER_FUNCS );
   lua_pushcfunction( L, luagi_note_iterator_free );
   lua_setfield( L, -2, "__gc" );

   luaL_newmetatable( L, LUAGI_CONFIG_ITERATOR_FUNCS );
   lua_pushcfunction( L, luagi_config_iterator_free );
   lua_setfield( L, -2, "__gc" );

   setup_funcs(L, LUAGI_TREE_FUNCS, luagi_tree_funcs);
   setup_funcs(L, LUAGI_TREE_ENTRY_FUNCS, luagi_tree_entry_funcs);
   setup_funcs(L, LUAGI_TREE_BUILDER_FUNCS, luagi_tree_builder_funcs);
   setup_funcs(L, LUAGI_BRANCH_FUNCS, luagi_branch_funcs);
   setup_funcs(L, LUAGI_COMMIT_FUNCS, luagi_commit_funcs);
   setup_funcs(L, LUAGI_REMOTE_FUNCS, luagi_remote_funcs);
   setup_funcs(L, LUAGI_STATUS_FUNCS, luagi_status_funcs );
   setup_funcs(L, LUAGI_DIFF_FUNCS, luagi_diff_funcs );
   setup_funcs(L, LUAGI_DIFF_STATS_FUNCS, luagi_diff_stats_funcs );
   setup_funcs(L, LUAGI_INDEX_FUNCS, luagi_index_funcs );
   setup_funcs(L, LUAGI_INDEX_CONFLICT_FUNCS, luagi_index_conflict_funcs );
   setup_funcs(L, LUAGI_OBJECT_FUNCS, luagi_object_funcs );
   setup_funcs(L, LUAGI_REFERENCE_FUNCS, luagi_reference_funcs );
   setup_funcs(L, LUAGI_REFERENCE_ITER_FUNCS, luagi_reference_iter_funcs );
   setup_funcs(L, LUAGI_ANNOTATED_COMMIT_FUNCS, luagi_annotated_commit_funcs );
   setup_funcs(L, LUAGI_BLOB_FUNCS, luagi_blob_funcs );
   setup_funcs(L, LUAGI_TAG_FUNCS, luagi_tag_funcs );
   setup_funcs(L, LUAGI_SUBMODULE_FUNCS, luagi_submodule_funcs );
   setup_funcs(L, LUAGI_NOTE_FUNCS, luagi_note_funcs );
   setup_funcs(L, LUAGI_BLAME_FUNCS, luagi_blame_funcs );
   setup_funcs(L, LUAGI_ODB_FUNCS, luagi_odb_funcs );
   setup_funcs(L, LUAGI_ODB_STREAM_FUNCS, luagi_odb_stream_funcs );
   setup_funcs(L, LUAGI_ODB_OBJECT_FUNCS, luagi_odb_object_funcs );
   setup_funcs(L, LUAGI_REFDB_FUNCS, luagi_refdb_funcs );
   setup_funcs(L, LUAGI_CONFIG_FUNCS, luagi_config_funcs );
   setup_funcs(L, LUAGI_INDEXER_FUNCS, luagi_indexer_funcs );
   setup_funcs(L, LUAGI_PATCH_FUNCS, luagi_patch_funcs );
   setup_funcs(L, LUAGI_PACK_FUNCS, luagi_pack_funcs );
   setup_funcs(L, LUAGI_REVWALK_FUNCS, luagi_revwalk_funcs );
   setup_funcs(L, LUAGI_REFLOG_FUNCS, luagi_reflog_funcs );
   setup_funcs(L, REPO_NAME, repofuncs);

   //TODO lua close hook to deinitialize git_libgit2_shutdown()
   luaL_newlib( L, mylib );
   return 1;
}

int signature_to_table( lua_State *L, const git_signature *sig )
{
   lua_newtable( L );
   if( sig == NULL )
      return 0;

   lua_pushstring( L, sig->name );
   lua_setfield( L, -2, NAME );
   lua_pushstring( L, sig->email );
   lua_setfield( L, -2, EMAIL );
   git_time time = sig->when;

   lua_pushnumber( L, time.time );
   lua_setfield( L, -2, TIME );

   lua_pushnumber( L, time.offset );
   lua_setfield( L, -2, TIME_OFF );
   return 0;
}
int table_to_signature( lua_State *L, git_signature **sig, int tablepos )
{
   lua_getfield( L, tablepos, NAME );
   const char *name = luaL_checkstring( L, -1 );
   lua_getfield( L, tablepos, EMAIL );
   const char *email = luaL_checkstring( L, -1 );
   lua_getfield( L, tablepos, TIME );
   git_time_t time = (git_time_t ) lua_tointeger( L, -1 );
   lua_getfield( L, tablepos, TIME_OFF );
   int offset = lua_tointeger( L, -1 );

   lua_pop( L, 4 );
   if( time == 0 )
   {
      return git_signature_now( sig, name, email );
   }
   else 
   {
      return git_signature_new( sig, name, email, time, offset );
   }
}

int luagi_push_transfer_stats( lua_State *L, const git_transfer_progress *stats )
{
   lua_newtable( L );
   lua_pushinteger( L,  stats->total_objects );
   lua_setfield( L, -2, TOTAL );
   lua_pushinteger( L,  stats->indexed_objects );
   lua_setfield( L, -2, INDEXED );
   lua_pushinteger( L,  stats->received_objects );
   lua_setfield( L, -2, RECEIVED );
   lua_pushinteger( L,  stats->local_objects );
   lua_setfield( L, -2, LOCAL );
   lua_pushinteger( L,  stats->total_deltas );
   lua_setfield( L, -2, DELTA );
   lua_pushinteger( L,  stats->indexed_deltas );
   lua_setfield( L, -2, INDEXED_DELTAS );
   lua_pushinteger( L,  stats->received_bytes );
   lua_setfield( L, -2, BYTES );
   
   return 1;
}
