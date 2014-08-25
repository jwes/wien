#include "reference.h"
#include <git2/refs.h>
#include <git2/oid.h>
#include "luagi.h"

int luagi_reference_lookup( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );

   git_reference **out = lua_newuserdata( L, sizeof( git_reference *) );
   if( git_reference_lookup( out, *repo, name ) )
   {
      ERROR_PUSH( L )
   }

   luaL_getmetatable( L, LUAGI_REFERENCE_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_reference_name_to_id( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );

   git_oid out;
   if(git_reference_name_to_id( &out, *repo, name ) )
   {
      ERROR_PUSH( L )
   }

   char buf[GIT_OID_HEXSZ + 1 ];
   lua_pushstring( L, git_oid_tostr( buf, sizeof(buf), &out ) );
   return 1;
}
   
int luagi_reference_dwim( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *shorthand = luaL_checkstring( L, 2 );

   git_reference **out = lua_newuserdata( L, sizeof( git_reference * ) );

   if( git_reference_dwim( out, *repo, shorthand ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_REFERENCE_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_reference_symbolic_create_matching( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_symbolic_create( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_create( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_create_matching( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

// reference methods
int luagi_reference_target( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_target_peel( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_symbolic_target( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_type( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_name( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_resolve( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_owner( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_symbolic_set_target( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_set_target( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_rename( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_delete( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_remove( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_list( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_foreach( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_foreach_name( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_is_branch( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_is_remote( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_is_tag( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_is_note( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_peel( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_shorthand( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_free( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }

// normal from glob and just names
int luagi_reference_iterator( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_iterator_free( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }

int luagi_reference_foreach_glob( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_has_log( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_ensure_log( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }
int luagi_reference_normalize_name( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }

int luagi_reference_is_valid_name( lua_State *L ){ luaL_error( L, "not yet implemented"); return 0; }


