#include "status.h"
#include "wien.h"
#include <git2/strarray.h>
#include <git2/diff.h>
#include <git2/status.h>
#include <git2/errors.h>
#define __USE_BSD
#include <string.h>
#undef __USE_BSD

#define INEW "index_new"
#define IMOD "index_modified"
#define IDEL "index_deleted"
#define IREN "index_renamed"
#define ITYP "index_typechange"

#define WNEW "workdir_new"
#define WMOD "workdir_modified"
#define WDEL "workdir_deleted"
#define WTYP "workdir_typechange"
#define WREN "workdir_renamed"

#define IGN "ignored"

int lgit_get_status_flags_from_lua( lua_State *L )
{
   lua_pushnil( L );
   return 1;
}

struct status_element {
   char *path;
   unsigned int status_flags;
   struct status_element *next;
};

struct status_list {
   struct status_element *next;
   struct status_element *last;
};

static void free_elem( struct status_element *elem )
{
   free( elem->path );
   free( elem );
}

static int lgit_status_callback( const char *path, unsigned int flags, void *payload)
{
   struct status_list* info = (struct status_list*) payload;

   struct status_element *elem = (struct status_element*) malloc( sizeof( struct status_element ));
   elem->path = strdup( path );
   elem->status_flags= flags;
   elem->next = NULL;

   if( info->last == NULL )
   {
      info->next = elem;
      info->last = elem;
   }
   else
   {
      info->last->next = elem;
      info->last = elem;
   }
   return 0;
}

static int lgit_status_walker( lua_State *L );
//function on repos
int lgit_status_foreach( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   git_status_options opts;
   if( git_status_init_options( &opts, GIT_STATUS_OPTIONS_VERSION ) )
   {
      luaL_error( L, "could not set up options" );
   }

   struct status_list* list = (struct status_list*) lua_newuserdata(L, sizeof(struct status_list ) );
   if( git_status_foreach( *repo, lgit_status_callback, list ) )
   {
      const git_error* err = giterr_last();
      luaL_error( L, "error iterating the files %s", err->message );
   }
   luaL_getmetatable(L, LGIT_STATUS_FOREACH);
   lua_setmetatable(L, -2);

   lua_pushcclosure( L, lgit_status_walker, 1 );
   return 1;
}

int lgit_status_foreach_ext( lua_State *L )
{
   lua_pushnil( L );
   return 1;
  
}

int lgit_status_file ( lua_State *L )
{
   lua_pushnil( L );
   return 1;
}

int lgit_status_list_new ( lua_State *L )
{
   lua_pushnil( L );
   return 1;
}

int lgit_status_should_ignore( lua_State *L )
{
   lua_pushnil( L );
   return 1;
}

// list operations
int lgit_status_list_entrycount( lua_State *L )
{
   lua_pushnil( L );
   return 1;
}

int lgit_status_by_index( lua_State *L )
{
   lua_pushnil( L );
   return 1;
}

int lgit_status_list_free( lua_State *L )
{
   lua_pushnil( L );
   return 1;
}

static int lgit_status_walker( lua_State *L )
{
   struct status_list* info = (struct status_list*) lua_touserdata( L, lua_upvalueindex( 1 ) );
   if ( info != NULL && info->next != NULL )
   {
      struct status_element *elem = info->next;
      info->next = elem->next;
      lua_pushstring( L, elem->path );
      // prepare boolean table to get rid of the integer flags
      const int f = elem->status_flags;
      lua_newtable( L );
      lua_pushboolean( L, f & GIT_STATUS_INDEX_NEW );
      lua_setfield( L, -2, INEW );
      lua_pushboolean( L, f & GIT_STATUS_INDEX_MODIFIED );
      lua_setfield( L, -2, IMOD );
      lua_pushboolean( L, f & GIT_STATUS_INDEX_DELETED );
      lua_setfield( L, -2, IDEL );
      lua_pushboolean( L, f & GIT_STATUS_INDEX_RENAMED );
      lua_setfield( L, -2, IREN );
      lua_pushboolean( L, f & GIT_STATUS_INDEX_TYPECHANGE );
      lua_setfield( L, -2, ITYP );
      lua_pushboolean( L, f & GIT_STATUS_WT_NEW );
      lua_setfield( L, -2, WNEW );
      lua_pushboolean( L, f & GIT_STATUS_WT_MODIFIED );
      lua_setfield( L, -2, WMOD );
      lua_pushboolean( L, f & GIT_STATUS_WT_DELETED );
      lua_setfield( L, -2, WDEL );
      lua_pushboolean( L, f & GIT_STATUS_WT_TYPECHANGE );
      lua_setfield( L, -2, WTYP );
      lua_pushboolean( L, f & GIT_STATUS_WT_RENAMED );
      lua_setfield( L, -2, WREN );
      lua_pushboolean( L, f & GIT_STATUS_IGNORED );
      lua_setfield( L, -2, IGN );

      free_elem( elem );
      return 2;
   }//iteration finished
   return 0;
}
