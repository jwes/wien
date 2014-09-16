#include <git2/refdb.h>
#include "refdb.h"
#include "luagi.h"

int luagi_refdb_new( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   git_refdb **refdb = lua_newuserdata( L, sizeof( git_refdb * ) );

   if( git_refdb_new( refdb, *repo ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_REFDB_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_refdb_open( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   git_refdb **refdb = lua_newuserdata( L, sizeof( git_refdb * ) );

   if( git_refdb_open( refdb, *repo ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_REFDB_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

   

//refdb
int luagi_refdb_compress( lua_State *L )
{
   git_refdb **refdb = checkrefdb_at( L, 1 );

   if( git_refdb_compress( *refdb ) )
   {
      ERROR_ABORT( L )
   }
   return 0;
}

int luagi_refdb_free( lua_State *L )
{
   git_refdb **refdb = checkrefdb_at( L, 1 );
   git_refdb_free( *refdb );
   return 0;
}
