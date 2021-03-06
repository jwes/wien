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
#include "submodule.h"

#include <git2/buffer.h>
#include <git2/submodule.h>

#include "ltk.h"
#include "luagi.h"
#include "oid.h"

int luagi_submodule_lookup( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );

   git_submodule **sub = lua_newuserdata( L, sizeof( git_submodule * ) );
   if( git_submodule_lookup( sub, *repo, name ) )
   {
      return ltk_push_git_error( L );
   }
   ltk_setmetatable( L, LUAGI_SUBMODULE_FUNCS );
   return 1;
}
int sub_foreach( git_submodule *sm, const char *name, void *payload )
{
   luagi_foreach_t *p = payload;

   lua_pushvalue( p->L, p->callback_pos );
   git_submodule **sub = lua_newuserdata( p->L, sizeof( git_submodule * ) );
   *sub = sm;
   ltk_setmetatable( p->L, LUAGI_SUBMODULE_FUNCS );

   lua_pushstring( p->L, name );

   if( lua_pcall( p->L, 2, 1, 0 ) )
   {
      luaL_error( p->L, "error calling the submodule callback" );
      return 1;
   }
   int ret = luaL_checkinteger( p->L, -1 );
   lua_pop( p->L, 1 );
   return ret;
}
int luagi_submodule_foreach( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   luaL_checktype( L, 2, LUA_TFUNCTION );
   luagi_foreach_t *p = malloc( sizeof( luagi_foreach_t ) );
   p->L = L;
   p->callback_pos = 2;

   if( git_submodule_foreach( *repo, sub_foreach, p ) )
   {
      ltk_error_abort( L );
   }
   free( p );
   return 0;
}
   
int luagi_submodule_add_setup( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *url = luaL_checkstring( L, 2 );
   const char *path = luaL_checkstring( L, 3 );
   int use_gitlink = lua_toboolean( L, 4 );
   
   git_submodule **sub = lua_newuserdata( L, sizeof( git_submodule * ) ); 
   if( git_submodule_add_setup( sub, *repo, url, path, use_gitlink ) )
   {
      return ltk_push_git_error( L );
   }
   ltk_setmetatable( L, LUAGI_SUBMODULE_FUNCS );
   return 1;
}

int luagi_submodule_resolve_url( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *url = luaL_checkstring( L, 2 );

   git_buf buf = GIT_BUF_INIT_CONST(NULL, 0);
   if( git_submodule_resolve_url( &buf, *repo, url ) )
   {
      return ltk_push_git_error( L );
   }

   lua_pushlstring( L, buf.ptr, buf.size );
   return 1;
}

int luagi_submodule_open( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );

   git_repository **out = lua_newuserdata( L, sizeof( git_repository* ) );

   if( git_submodule_open( out, *sub ) )
   {
      return ltk_push_git_error( L );
   }
   luaL_getmetatable( L, REPO_NAME );
   lua_setmetatable( L, -2 );
   return 1;
}

int luagi_submodule_free( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   git_submodule_free( *sub );
   return 0;
}

int luagi_submodule_add_finalize( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   if( git_submodule_add_finalize( *sub ) )
   {
      ltk_error_abort( L );
   }
   return 0;
}

static int luagi_sub_get_string( lua_State *L, const char * (*func)( git_submodule *sub ) )
{
   git_submodule **sub = checksubmodule_at( L, 1 );

   lua_pushstring( L, func( *sub ) );
   return 1;
}

int luagi_submodule_name( lua_State *L )
{
   return luagi_sub_get_string( L, git_submodule_name );
}

int luagi_submodule_path( lua_State *L )
{
   return luagi_sub_get_string( L, git_submodule_path );
}
int luagi_submodule_url( lua_State *L )
{
   return luagi_sub_get_string( L, git_submodule_url );
}

int luagi_submodule_branch( lua_State *L )
{
   return luagi_sub_get_string( L, git_submodule_branch );
}

static int luagi_sub_set_string( lua_State *L, int (*func)( git_repository *repo, const char *name, const char *str ) )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );
   const char *str = luaL_checkstring( L, 2 );

   if( func( *repo, name, str ) )
   {
      ltk_error_abort( L );
   }
   return 0;
}

int luagi_submodule_set_url( lua_State *L )
{
   return luagi_sub_set_string( L, git_submodule_set_url );
}

static int luagi_sub_get_id( lua_State *L, const git_oid * (*func)(git_submodule *sub ) )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   const git_oid *oid = func( *sub );
   return luagi_push_oid( L, oid );
}

int luagi_submodule_index_id( lua_State *L )
{
   return luagi_sub_get_id( L, git_submodule_index_id );
}

int luagi_submodule_head_id( lua_State *L )
{
   return luagi_sub_get_id( L, git_submodule_head_id );
}

int luagi_submodule_wd_id( lua_State *L )
{
   return luagi_sub_get_id( L, git_submodule_wd_id );
}

static int luagi_sub_push_ignore( lua_State *L, git_submodule_ignore_t ignore )
{
   switch ( ignore )
   {
      default:
      case GIT_SUBMODULE_IGNORE_NONE: 
         lua_pushstring( L, NONE );
         break;
      case GIT_SUBMODULE_IGNORE_UNTRACKED: 
         lua_pushstring( L, UNTRACKED );
         break;
      case GIT_SUBMODULE_IGNORE_DIRTY: 
         lua_pushstring( L, DIRTY );
         break;
      case GIT_SUBMODULE_IGNORE_ALL: 
         lua_pushstring( L, ALL );
         break;
   }
   return 1;
}

git_submodule_ignore_t luagi_sub_check_ignore( lua_State *L, int index )
{
   const char *ignore = luaL_checkstring( L, index );
   
   switch( ignore[0] )
   {
      default:
      case 'a':
         return GIT_SUBMODULE_IGNORE_ALL;
      case 'd':
         return GIT_SUBMODULE_IGNORE_DIRTY;
      case 'n':
         return GIT_SUBMODULE_IGNORE_NONE;
      case 'u':
         return GIT_SUBMODULE_IGNORE_UNTRACKED;
   }         
}

int luagi_submodule_ignore( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   git_submodule_ignore_t type = git_submodule_ignore( *sub );
   return luagi_sub_push_ignore( L, type );
}

int luagi_submodule_set_ignore( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );
   git_submodule_ignore_t ign = luagi_sub_check_ignore( L, 3 );

   git_submodule_ignore_t old =  git_submodule_set_ignore( *repo, name, ign );
   return luagi_sub_push_ignore( L, old );
}

static int luagi_sub_push_update( lua_State *L, git_submodule_update_t update )
{
   switch ( update )
   {
      default:
      case GIT_SUBMODULE_UPDATE_NONE:
              // none is none, use IGNORE define
         lua_pushstring( L, NONE );
         break;
      case GIT_SUBMODULE_UPDATE_CHECKOUT:
         lua_pushstring( L, CHECKOUT );
         break;
      case GIT_SUBMODULE_UPDATE_MERGE:
         lua_pushstring( L, MERGE );
         break;
      case GIT_SUBMODULE_UPDATE_REBASE:
         lua_pushstring( L, REBASE );
         break;
      case GIT_SUBMODULE_UPDATE_DEFAULT:
         lua_pushstring( L, DEFAULT );
         break;
   }
   return 1;
}

static git_submodule_update_t luagi_sub_check_update( lua_State *L, int index )
{
   const char *update = luaL_checkstring( L, index );
   
   switch( update[0] )
   {
      case 'c':
         return GIT_SUBMODULE_UPDATE_CHECKOUT;
      case 'm':
         return GIT_SUBMODULE_UPDATE_MERGE;
      case 'n':
         return GIT_SUBMODULE_UPDATE_NONE;
      case 'r':
         if( update[2] == 'b' )
         {
            return GIT_SUBMODULE_UPDATE_REBASE;
         }
      default:
         return GIT_SUBMODULE_UPDATE_DEFAULT;
   }         
   return GIT_SUBMODULE_UPDATE_DEFAULT;
}

static int luagi_init_submodule_update_options(
                git_submodule_update_options *opts,
                lua_State *L,
                int table_index )
{
   git_submodule_update_init_options( opts, GIT_SUBMODULE_UPDATE_OPTIONS_VERSION );
   if( lua_type( L, table_index) == LUA_TTABLE )
   {
   }
   return 0;
}

int luagi_submodule_update( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   git_submodule_update_options opts;
   luagi_init_submodule_update_options( &opts, L, 2 );

   int init = luaL_optinteger( L, 3, 0 );

   int ret = git_submodule_update( *sub, init, &opts );
   if( ret )
   {
      ltk_error_abort( L );
   }
   return 0;
}

int luagi_submodule_update_strategy( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   git_submodule_update_t t = git_submodule_update_strategy( *sub );
   return luagi_sub_push_update( L, t );
}

int luagi_submodule_set_update( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );
   git_submodule_update_t value = luagi_sub_check_update( L, 3 );
   git_submodule_update_t t = git_submodule_set_update( *repo, name, value );
   return luagi_sub_push_update( L, t );
}

static int luagi_sub_push_recurse( lua_State *L, git_submodule_recurse_t recurse )
{
   switch ( recurse )
   {
      default:
      case GIT_SUBMODULE_RECURSE_NO:
         lua_pushstring( L, RECURSE_NO );
         break;
      case GIT_SUBMODULE_RECURSE_YES:
         lua_pushstring( L, RECURSE_YES );
         break;
      case GIT_SUBMODULE_RECURSE_ONDEMAND:
         lua_pushstring( L, RECURSE_ONDEMAND );
         break;
   }
   return 1;
}

static git_submodule_recurse_t luagi_sub_check_recurse( lua_State *L, int index )
{
   const char *recurse = luaL_checkstring( L, index );
   
   switch( recurse[0] )
   {
      case 'y':
         return GIT_SUBMODULE_RECURSE_YES;
      case 'n':
      default:
         return GIT_SUBMODULE_RECURSE_NO;
      case 'o':
         return GIT_SUBMODULE_RECURSE_ONDEMAND;
   }         
}



int luagi_submodule_fetch_recurse_submodules( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   git_submodule_recurse_t t = git_submodule_fetch_recurse_submodules( *sub );
   return luagi_sub_push_recurse( L, t );
}

int luagi_submodule_set_fetch_recurse_submodules( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );
   git_submodule_recurse_t recurse = luagi_sub_check_recurse( L, 3 );
   git_submodule_recurse_t t = git_submodule_set_fetch_recurse_submodules( *repo, name, recurse );
   return luagi_sub_push_recurse( L, t );
}

int luagi_submodule_init( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   int overwrite = lua_toboolean( L, 2 );

   if( git_submodule_init( *sub, overwrite ) )
   {
      ltk_error_abort( L );
   }
   return 0;
}

int luagi_submodule_sync( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );

   if( git_submodule_sync( *sub ) )
   {
      ltk_error_abort( L );
   }
   return 0;
}

int luagi_submodule_reload( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   int force = lua_toboolean( L, 2 );

   if( git_submodule_reload( *sub, force ) )
   {
      ltk_error_abort( L );
   }
   return 0;
}
static void push_flag_to_table( lua_State *L, const unsigned int bitfield, const char *name, const unsigned int flag )
{
   lua_pushboolean( L, bitfield & flag );
   lua_setfield( L, -2, name );
}

static int luagi_push_status( lua_State *L, const unsigned int status )
{
   lua_newtable( L );
   push_flag_to_table( L, status, IN_HEAD, GIT_SUBMODULE_STATUS_IN_HEAD);
   push_flag_to_table( L, status, IN_INDEX, GIT_SUBMODULE_STATUS_IN_INDEX);
   push_flag_to_table( L, status, IN_CONFIG, GIT_SUBMODULE_STATUS_IN_CONFIG);
   push_flag_to_table( L, status, IN_WD, GIT_SUBMODULE_STATUS_IN_WD);
   lua_newtable( L );
   push_flag_to_table( L, status, ADDED, GIT_SUBMODULE_STATUS_INDEX_ADDED);
   push_flag_to_table( L, status, DELETED, GIT_SUBMODULE_STATUS_INDEX_DELETED);
   push_flag_to_table( L, status, MODIFIED, GIT_SUBMODULE_STATUS_INDEX_MODIFIED);
   lua_setfield( L, -2, INDEX );
   lua_newtable( L );
   push_flag_to_table( L, status, UNINITIALIZED, GIT_SUBMODULE_STATUS_WD_UNINITIALIZED);
   push_flag_to_table( L, status, ADDED, GIT_SUBMODULE_STATUS_WD_ADDED);
   push_flag_to_table( L, status, DELETED, GIT_SUBMODULE_STATUS_WD_DELETED );
   push_flag_to_table( L, status, MODIFIED, GIT_SUBMODULE_STATUS_WD_MODIFIED);
   push_flag_to_table( L, status, IMOD, GIT_SUBMODULE_STATUS_WD_INDEX_MODIFIED);
   push_flag_to_table( L, status, WMOD, GIT_SUBMODULE_STATUS_WD_WD_MODIFIED);
   push_flag_to_table( L, status, UNTRACKED, GIT_SUBMODULE_STATUS_WD_UNTRACKED);
   lua_setfield( L, -2, WORKDIR );

   return 1;
}

int luagi_submodule_status( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *name = luaL_checkstring( L, 2 );
   git_submodule_ignore_t ignore = luagi_sub_check_ignore( L, 3 );

   unsigned int status;

   if( git_submodule_status( &status, *repo, name, ignore ) )
   {
      return ltk_push_git_error( L );
   }

   return luagi_push_status( L, status );
}

int luagi_submodule_location( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );

   unsigned int status = 0;
   if( git_submodule_location( &status, *sub ) )
   {
      return ltk_push_git_error( L );
   }
   return luagi_push_status( L, status );
}

int luagi_submodule_add_to_index( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   int write_index = lua_toboolean( L, 2 );

   if( git_submodule_add_to_index( *sub, write_index ) )
   {
      ltk_error_abort( L );
   }
   return 0;
}

int luagi_submodule_repo_init( lua_State *L )
{
   git_submodule **sub = checksubmodule_at( L, 1 );
   int use_gitlink = lua_toboolean( L, 2 );

   git_repository **repo = lua_newuserdata(L, sizeof(git_repository *) );

   if( git_submodule_repo_init( repo, *sub, use_gitlink ) )
   {
      return ltk_push_git_error( L );
   }
   ltk_setmetatable( L, REPO_NAME );
   return 1;
}
