#ifndef IS_LUAGI_DEFINES
#define IS_LUAGI_DEFINES

#define NAME "name"
#define OID "oid"
#define LOID "loid"
#define TARGET "target"
#define LOCAL "local"

#define EMAIL "email"
#define TIME "time"
#define TIME_OFF "time_offset"

#define ID "id"
#define SIZE "size"
#define FLAGS "flags"
#define MODE "mode"

#define STATUS "status"
#define SIMI "similarity"
#define NFILES "number_of_files"
#define OLD_FILE "old_file"
#define NEW_FILE "new_file"

#define BINARY "binary"
#define NOT_BINARY "not_binary"
#define VALID_ID "valid_id"

#define PATCH "patch"
#define HEADER "header"
#define RAW "raw"
#define NAME_ONLY "name_only"
#define NAME_STATUS "name_status"

#define ADDED "added"
#define DELETED "deleted"
#define MODIFIED "modified"
#define RENAMED "renamed"
#define COPIED "copied"
#define IGNORED "ignored"
#define UNTRACKED "untracked"
#define TYPECHANGE "typechange"

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

#define INVALID "invalid"
#define SYMBOLIC "symbolic"

#define OLD "old"
#define NEW "new"
#define COMMITTER "committer"
#define MESSAGE "message"

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

#define IGNOREED           "ignored"

#define SHOW               "show"
#define FLAGS              "flags"
#define PATHS              "paths"

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

#define STATUS           "status"
#define IDX_TO_WRK       "index_to_workdir"
#define HEAD_TO_IDX      "head_to_index"

#define UNTRACKED "untracked"
#define DIRTY "dirty"
#define ALL "all"
#define DEFAULT "default"

#define CHECKOUT "checkout"
#define REBASE "rebase"
#define MERGE "merge"

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

#define BLOB_EXECUTABLE "blob_executable"
#define LINK "link"

#define SSH "ssh"
#define HTTP "http"

#define LINES_IN_HUNK "lines_in_hunk"
#define FINAL "final"
#define ORIG "orig"
#define IS_BOUNDARY "is_boundary"
#define START_LINE_NUMBER "start_line_number"
#define SIGNATURE "signature"

#define DIRECTION "direction"
#define STRING "representation"
#define SRC "src"
#define DEST "dest"
#define PUSH "push"
#define FETCH "fetch"
#define UNKNOWN "unknown"
#define FORCE "force"
#define ALL "all"
#define AUTO "auto"
#define TOTAL "total"
#define DELTA "delta"
#define INDEXED_DELTAS "indexed_deltas"
#define BYTES "bytes"
#define RECEIVED "received"
#define INDEXED "indexed"

#define ORIGIN "origin"
#define OLD_LINENO "old linenr"
#define NEW_LINENO "old linenr"
#define LINES "lines"

#define OLD_START "old start"
#define OLD_LINES "old lines"
#define NEW_START "new start"
#define NEW_LINES "new lines"

#define MIN_MATCH "min_match"
#define NEWEST "newest"
#define OLDEST "oldest"
#define MIN_LINE "min_line"
#define MAX_LINE "max_line"
#define COPIES_IN_SAME_COMMIT_MOVES "copies_in_same_commit_moves"
#define COPIES_IN_SAME_COMMIT_COPIES "copies_in_same_commit_copies"
#define COPIES_ANY_COMMIT_COPIES "copies_in_any_commit_copies"
#define FIRST_PARENT "first_parent"
#define COPIES_IN_SAME_FILE "copies_in_same_file"

#define SHOW_BINARY "show_binary"
#define MINIMAL "minimal"
#define PATIENCE "patience"
#define SHOW_UNMODIFIED "show_unmodified"
#define SHOW_UNTRACKED_CONTENT "show_untracked_content"
#define IGNORE_WHITESPACE_EOL "ignore_whitespace_eol"
#define INCLUDE_IGNORED "ignored_ignored"
#define IGNORE_WHITESPACE "ignore_whitespace"
#define IGNORE_WHITESPACE_CHANGE "ignore_whitespace_change"
#define FORCE_BINARY "force_binary"
#define FORCE_TEXT "force_text"
#define ENABLE_FAST_UNTRACKED_DIRS "enable_fast_untacked_dirs"
#define UPDATE_INDEX "update_index"
#define SKIP_BINARY_CHECK "skip_binary_check"
#define IGNORE_SUBMODULES "ignore_submodules"
#define IGNORE_FILEMODE "ignore_filemode"
#define INCLUDE_TYPECHANGE "include_typechange"
#define INCLUDE_TYPECHANGE_TREES "include_typechange_trees"
#define RECURSE_UNTRACKED_DIRS "recurse_untracked_dirs"
#define INCLUDE_UNMODIFIED "include_unmodified"
#define RECURSE_IGNORED_DIRS "recurse_ignored_dirs"
#define REVERSE "reverse"
#define INCLUDE_UNTRACKED "include_untracked"
#define IGNORE_SUBMODULES_TYPE "ignore_submodule_type"
#define PATHSPEC "pathspec"
#define CONTEXT_LINES "context_lines"
#define INTERHUNK_LINES "interhunk_lines"
#define ID_ABBREV "id_abbrev"
#define MAX_SIZE "max_size"
#define OLD_PREFIX "old_prefix"
#define NEW_PREFIX "new_prefix"

#define REMOVE_UNMODIFIED "remove_unmodified"
#define REWRITES_FOR_RENAMES_ONLY "rewrites_for_renames_only"
#define EXACT_MATCH_ONLY "exact_match_only"
#define DONT_IGNORE_WHITESPACE "dont_ignore_whitespace"
#define FOR_UNTRACKED "for_untracked"
#define REWRITES "rewrites"
#define BREAK_REWRITES "break_rewrites"
#define COPIES_FROM_UNMODIFIED "copies_from_unmodified"
#define COPIES "copies"
#define RENAMES "renames"
#define RENAMES_FROM_REWRITES "renames_from_rewrites"
#define BY_CONFIG "by_config"
#define RENAME_THRESHOLD "rename_threshold"
#define RENAME_FROM_REWRITE_THRESHOLD "rename_from_rewrite_threshold"
#define COPY_THRESHOLD "copy_threshold"
#define BREAK_REWRITE_THRESHOLD "break_rewrite_threshold"
#define RENAME_LIMIT "rename_limit"

#define EXCLUDE_SUBJECT_PATCH_MARKER "exclude_subject_patch_marker"
#define PATCH_NO "patch_no"
#define TOTAL_PATCHES "total_patches"
#define SUMMARY "summary"
#define AUTHOR "author"

#define FILE_FAVOR "file_favor"
#define FIND_RENAMES "find_renames"
#define TARGET_LIMIT "target_limit"
#define OUR_LABEL "our_label"
#define THEIR_LABEL "their_label"
#define ANCESTOR_LABEL "ancestor_label"

#define SIMPLIFY_ALNUM "simplify_alnum"
#define STYLE_DIFF3 "style_diff3"
#define STYLE_MERGE "style_merge"

#define CROSS_FS "cross_fs"
#define BARE "bare"
#define NO_REINIT "no_reinit"
#define NO_DOTGIT_DIR "no_dotgit_dir"
#define MKDIR "mkdir"
#define MKPATH "mkpath"
#define EXTERNAL_TEMPLATE "external_template"

#define WORKDIR_PATH "workdir_path"
#define DESCRIPTION "description"
#define TEMPLATE_PATH "template_path"
#define INITIAL_HEAD "initial_head"
#define ORIGIN_URL "origin_url"

#define REFSPEC_PATTERN "refspec_pattern"
#define REFSPEC_SHORTHAND "refspec_shorthand"
#define ALLOW_ONELEVEL "allow_onelevel"
#define KEEP_INDEX "keep_index"
#define INDEX "index"
#define WORKDIR "workdir"

#define IN_HEAD "in_head"
#define IN_INDEX "in_index"
#define IN_CONFIG "in_config"
#define IN_WD "in_workdir"
#define UNINITIALIZED "uninitalized"
#define THREADS "threads"

#define SYSTEM "system"
#define XDG "xdg"
#define GLOBAL "global"
#define APP "app"
#define HIGHEST "highest"

#define SAFE "safe"
#define SAFE_CREATE "safe_create"
#define ALLOW_CONFLICTS "allow_conflicts"
#define REMOVE_UNTRACKED "remove_untracked"
#define REMOVE_IGNORED "remove_ignored"
#define UPDATE_ONLY "update_only"
#define DONT_UPDATE_INDEX "dont_update_index"
#define NO_REFRESH "no_refresh"
#define SKIP_UNMERGED "skip_unmerged"
#define USE_OURS "use_ours"
#define USE_THEIRS "use_theirs"
#define DISABLE_PATHSPEC_MATCH "disable_pathspec_match"
#define SKIP_LOCKED_DIRECTORIES "skip_locked_directories"
#define DONT_OVERWRITE_IGNORED "dont_overwrite_ignored"
#define CONFLICT_STYLE_MERGE "conflict_style_merge"
#define CONFLICT_STYLE_DIFF3 "conflict_style_diff3"
#define UPDATE_SUBMODULES "update_submodules"
#define UPDATE_SUBMODULES_IF_CHANGED "update_submodules_if_changed"

#define DISABLE_FILTERS "disable_filters"
#define BASELINE "baseline"
#define UPDATED "updated"
#define NOTIFY_FLAGS "notify_flags"
#define CONFLICT "conflict"
#define DIR_MODE "dir_mode"
#define FILE_MODE "file_mode"
#define FILE_OPEN_FLAGS "file_open_flags"

#define REVERT "revert"
#define CHERRY_PICK "cherry_pick"
#define BISECT "bisect"
#define REBASE_INTERACTIVE "rebase_interactive"
#define REBASE_MERGE "rebase_merge"
#define APPLY_MAILBOX "apply_mailbox"
#define APPLY_MAILBOX_OR_REBASE "apply_mailbox_or_rebase"
#define OURS "ours"
#define THEIRS "theirs"
#define CLEAN "clean"
#define ANCESTOR "ancestor"

#endif
