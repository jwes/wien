#ifndef IS_LUAGI_DEFINES
#define IS_LUAGI_DEFINES

#define KEY_NAME "name"
#define KEY_OID "oid"
#define KEY_LOID "loid"
#define KEY_TARGET "target"
#define KEY_LOCAL "local"

#define KEY_EMAIL "email"
#define KEY_TIME "time"
#define KEY_TIME_OFF "time_offset"

#define VALUE_ANY "any"
#define VALUE_INVALID "invalid"
#define VALUE_RESERVED "reserved for future use"
#define VALUE_COMMIT "commit"
#define VALUE_TREE "tree"
#define VALUE_BLOB "blob"
#define VALUE_TAG "tag"
#define VALUE_OFS_DELTA "ofs_delta"
#define VALUE_REF_DELTA "ref_delta"
#define DIFF_FILE_ID "id"
#define DIFF_FILE_PATH "path"
#define DIFF_FILE_SIZE "size"
#define DIFF_FILE_FLAGS "flags"
#define DIFF_FILE_MODE "mode"

#define DIFF_DELTA_STATUS "status"
#define DIFF_DELTA_FLAGS "flags"
#define DIFF_DELTA_SIMI "similarity"
#define DIFF_DELTA_NFILES "number_of_files"
#define DIFF_DELTA_OLD_FILE "old_file"
#define DIFF_DELTA_NEW_FILE "new_file"

#define BINARY "binary"
#define NOT_BINARY "not_binary"
#define VALID_ID "valid_id"

#define PATCH "patch"
#define PATCH_HEADER "patch_header"
#define RAW "raw"
#define NAME_ONLY "name_only"
#define NAME_STATUS "name_status"

#define D_ADDED "added"
#define D_DELETED "deleted"
#define D_MODIFIED "modified"
#define D_RENAMED "renamed"
#define D_COPIED "copied"
#define D_IGNORED "ignored"
#define D_UNTRACKED "untracked"
#define D_TYPECHANGE "typechange"

#define NONE "none"
#define NORMAL "normal"
#define UP_TO_DATE "up to date"
#define FASTFORWARD "fast forward"
#define UNBORN "unborn"

#define NO_FASTFORWARD "no fast forward"
#define FASTFORWARD_ONLY "fast forward only"

#define PATH "path"
#define CONTENT "content"
#define FORCE "force"
#define DISABLE_PATHSPEC_MATCH "disable_pathspec_match"
#define CHECK_PATHSPEC "check_pathspec"

#define IGNORE_CASE "ignore_case"
#define NO_FILEMODE "no_filemode"
#define NO_SYMLINKS "no_symlinks"
#define FROM_OWNER "from_owner"

#define REF_INVALID "invalid"
#define REF_OID "oid"
#define REF_SYMBOLIC "symbolic"

#define KEY_OLD "old"
#define KEY_NEW "new"
#define KEY_COMMITTER "committer"
#define KEY_MESSAGE "message"

#define SOFT "soft"
#define MIXED "mixed"
#define HARD "hard"

#define INEW               "index_new"
#define IMOD               "index_modified"
#define IDEL               "index_deleted"
#define IREN               "index_renamed"
#define ITYP               "index_typechange"

#define WNEW               "workdir_new"
#define WMOD               "workdir_modified"
#define WDEL               "workdir_deleted"
#define WTYP               "workdir_typechange"
#define WREN               "workdir_renamed"

#define IGN                "ignored"

#define LUAGI_SHOW          "show"
#define LUAGI_FLAGS         "flags"
#define LUAGI_PATHS         "paths"

#define INC_UNTRACKED      "include_untracked"
#define INC_IGNORED        "include_ignored"
#define INC_UNMODIFIED     "include_unmodified"
#define EX_SUBMODULES      "exclude_submoduled"
#define REC_UNTRACKED_DIRS "recurse_untracked_dirs"
#define DISABLE_PATHSPEC   "diable_pathspec_match"
#define REC_IGNORED_DIRS   "recurse_ignored_dirs"
#define REN_HEAD_TO_IDX    "rename_head_to_index"
#define REN_IDX_TO_WDIR    "rename_index_to_workdir"
#define SORT_SENSI         "sort_case_sensitively"
#define SORT_INSENSI       "sort_case_insensitively"
#define REN_FROM_REWRITE   "renames_from_rewrites"
#define NO_REFRESH         "no_refresh"

#define L_STATUS           "index_to_workdir"
#define L_IDX_TO_WRK       "index_to_workdir"
#define L_HEAD_TO_IDX      "head_to_index"

#define IGNORE_NONE "none"
#define IGNORE_UNTRACKED "untracked"
#define IGNORE_DIRTY "dirty"
#define IGNORE_ALL "all"
#define IGNORE_DEFAULT "default"

#define UPDATE_CHECKOUT "checkout"
#define UPDATE_REBASE "rebase"
#define UPDATE_MERGE "merge"
#define UPDATE_NONE "none"

#define RECURSE_YES "yes"
#define RECURSE_NO "no"
#define RECURSE_ONDEMAND "on_demand"

#define ANY "any"
#define BAD "bad"
#define _EXT1 "_ext1"
#define COMMIT "commit"
#define TREE "tree"
#define BLOB "blob"
#define TAG "tag"
#define _EXT2 "_ext2"
#define OFS_DELTA "ofs_delta"
#define REF_DELTA "ref_delta"

#define SSH "ssh"
#define HTTP "http"

#define BLAME_LINES_IN_HUNK "lines_in_hunk"
#endif
