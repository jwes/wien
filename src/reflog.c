#include "reflog.h"
#include "luagi.h"
#include "oid.h"

int luagi_reflog_read( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );

   git_reflog **log = lua_newuserdata( L, sizeof( git_reflog *) );

   if( git_reflog_read( log, *repo, name ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_REFLOG_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}
   
int luagi_reflog_rename( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *oldname = luaL_checkstring( L, 2 );
   const char *name = luaL_checkstring( L, 3 );

   if( git_reflog_rename( *repo, oldname, name ) )
   {
      ERROR_ABORT( L )
   }
   return 0;
}

int luagi_reflog_delete( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );
   
   if( git_reflog_delete( *repo, name ) )
   {
      ERROR_ABORT( L );
   }
   return 0;
}


//reflog
int luagi_reflog_write( lua_State *L )
{
   git_reflog **log = checkreflog( L );

   if( git_reflog_write( *log ) )
   {
      ERROR_ABORT( L ) 
   }
   return 0;
}

int luagi_reflog_append( lua_State *L )
{
   git_reflog **log = checkreflog( L );
   git_oid oid;
   luagi_check_oid( &oid, L, 2 );
   git_signature sig;
   table_to_signature( L, &sig, 3 );
   const char *msg = luaL_checkstring( L, 4 );

   if( git_reflog_append( *log, &oid, &sig, msg ) )
   {
      ERROR_ABORT( L )
   }
   return 0;
}

int luagi_reflog_entrycount( lua_State *L )
{
   git_reflog **log = checkreflog( L );
   size_t size = git_reflog_entrycount( *log );
   lua_pushinteger( L, size );
   return 1;
}

int luagi_reflog_entry_byindex( lua_State *L )
{
   git_reflog **log = checkreflog( L );
   size_t idx = luaL_checkinteger( L, 2 );

   const git_reflog_entry *entry = git_reflog_entry_byindex( *log, idx );
   if( entry == NULL )
   {
      ERROR_PUSH( L )
   }

   return luagi_reflog_entry_totable( L, entry );
}

int luagi_reflog_drop( lua_State *L )
{
   git_reflog **log = checkreflog( L );
   size_t idx = luaL_checkinteger( L, 2 );
   int rewrite_previous_entry = lua_toboolean( L, 3 );
   if( git_reflog_drop( *log, idx, rewrite_previous_entry ) )
   {
      ERROR_ABORT( L )
   }
   return 0;
}
   
int luagi_reflog_entry_totable( lua_State *L, const git_reflog_entry *entry )
{
   const git_oid *oid = git_reflog_entry_id_old( entry );

   int ret = luagi_push_oid( L, oid );


   //TODO 
   return ret;
}

int luagi_reflog_free( lua_State *L )
{
   git_reflog **log = checkreflog( L );
   git_reflog_free( *log );
   return 0;
}

