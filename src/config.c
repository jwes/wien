#include <git2/config.h>
#include "config.h"
#include "luagi.h"

//general
static int luagi_find_config( lua_State *L, int (*func)( git_buf *out ) )
{
   git_buf buf;
   if( func( &buf ) )
   {
      ERROR_PUSH( L )
   }
   lua_pushlstring( L, buf.ptr, buf.size );
   return 1;
}
   
int luagi_config_find_global( lua_State *L )
{
   return luagi_find_config( L, git_config_find_global );
}

int luagi_config_find_xdg( lua_State *L )
{
   return luagi_find_config( L, git_config_find_xdg );
}

int luagi_config_find_system( lua_State *L )
{
   return luagi_find_config( L, git_config_find_system );
}

int luagi_config_open_default( lua_State *L )
{
   git_config **cfg = lua_newuserdata( L, sizeof( git_config *) );

   if( git_config_open_default( cfg ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_CONFIG_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_config_new( lua_State *L )
{
   git_config **cfg = lua_newuserdata( L, sizeof( git_config *) );

   if( git_config_new( cfg ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_CONFIG_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_config_open_ondisk( lua_State *L )
{
   const char *path = luaL_checkstring( L, 1 );
   git_config **cfg = lua_newuserdata( L, sizeof( git_config *) );

   if( git_config_open_ondisk( cfg, path ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_CONFIG_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

static git_config_level_t luagi_check_level( lua_State *L, int index )
{
   //TODO config_level from string instead of int
   int level = luaL_checkinteger( L, index );
   // TODO if not, at least check bounds
   return level;
}
static int luagi_push_level( lua_State *L, git_config_level_t level )
{
   //TODO config_level from string instead of int
   lua_pushinteger( L, level );
   return 1;
}
   
// config
int luagi_config_add_file_ondisk( lua_State *L )
{
   git_config **cfg = checkconfig( L );
   const char *path = luaL_checkstring( L, 2 );
   git_config_level_t level = luagi_check_level( L, 3 );
   int force = lua_toboolean( L, 4 );

   if( git_config_add_file_ondisk( *cfg, path, level, force ) )
   {
      ERROR_ABORT( L )
   }
   return 0;
}

int luagi_config_open_level( lua_State *L )
{
   git_config **cfg = checkconfig( L );
   git_config_level_t level = luagi_check_level( L, 2 );

   git_config **out = lua_newuserdata( L, sizeof( git_config * ) );

   if( git_config_open_level( out, *cfg, level ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_CONFIG_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_config_open_global( lua_State *L )
{
   git_config **cfg = checkconfig( L );

   git_config **out = lua_newuserdata( L, sizeof( git_config * ) );

   if( git_config_open_global( out, *cfg ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_CONFIG_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_config_snapshot( lua_State *L )
{
   git_config **cfg = checkconfig( L );

   git_config **out = lua_newuserdata( L, sizeof( git_config * ) );

   if( git_config_snapshot( out, *cfg ) )
   {
      ERROR_PUSH( L )
   }
   luaL_getmetatable( L, LUAGI_CONFIG_FUNCS );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_config_refresh( lua_State *L )
{
   git_config **cfg = checkconfig( L );

   if( git_config_refresh( *cfg ) )
   {
      ERROR_ABORT( L )
   }
   return 0;
}
static int luagi_push_config_entry( lua_State *L, const git_config_entry *entry )
{
   lua_pushstring( L, entry->value );
   lua_pushstring( L, entry->name );
   luagi_push_level( L, entry->level );
   return 3;
}

int luagi_config_get_entry( lua_State *L )
{
   git_config **cfg = checkconfig( L );
   const char *name = luaL_checkstring( L, 2 );

   const git_config_entry *entry;
   if( git_config_get_entry( &entry, *cfg, name ) )
   {
      ERROR_PUSH( L )
   }

   return luagi_push_config_entry( L, entry );
}
     
int luagi_config_get_int32( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_get_int64( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_get_bool( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_get_string( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

int luagi_config_get_mulitvar_foreach( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

int luagi_config_iterator_new( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_iterator_glob_new( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_multivar_iterator( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_iterator_free( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

int luagi_config_set_int32( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_set_int64( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_set_bool( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_set_string( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_set_multivar( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_delete_entry( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_delete_mulitvar( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

int luagi_config_foreach( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_foreach_match( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

//TODO mapping
int luagi_config_get_mapped( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_lookup_map_value( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

int luagi_config_parse_bool( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_parse_int32( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }
int luagi_config_parse_int64( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

int luagi_config_backend_foreach_match( lua_State *L ){ luaL_error( L, "not yet implemented" ); return 0; }

int luagi_config_free( lua_State *L )
{
   git_config **cfg = checkconfig_at( L, 1 );
   git_config_free( *cfg );
   return 0;
}
