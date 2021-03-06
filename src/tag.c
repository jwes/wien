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
#include "tag.h"

#include <git2/signature.h>
#include <git2/tag.h>

#include "ltk.h"
#include "luagi.h"
#include "object.h"
#include "oid.h"
#include "types.h"

int luagi_tag_lookup( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   git_oid id;
   int len, ret = 0;
   luagi_check_oid_prefix( &id, &len, L, 2 );

   git_tag **out = lua_newuserdata( L, sizeof( git_tag * ) ); 
   ret =  git_tag_lookup_prefix( out, *repo, &id, len );

   if( ret )
   {
      return ltk_push_git_error( L );
   }
   ltk_setmetatable( L, LUAGI_TAG_FUNCS );
   return 1;
}

int luagi_tag_create( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *tag_name = luaL_checkstring( L, 2 );
   git_object **obj = checkobject_at( L, 3 );
   git_signature *sig;
   table_to_signature( L, &sig, 4 );
   const char *message = luaL_checkstring( L, 5 );
   int force = lua_toboolean( L, 6 );

   git_oid out;
   int ret = git_tag_create( &out, *repo, tag_name, *obj, sig, message, force );
   git_signature_free( sig );
   if(ret)
   {
      return ltk_push_git_error( L );
   }
   return luagi_push_oid( L, &out );
}

int luagi_tag_annotation_create( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *tag_name = luaL_checkstring( L, 2 );
   git_object **obj = checkobject_at( L, 3 );
   git_signature *sig;
   table_to_signature( L, &sig, 4 );
   const char *message = luaL_checkstring( L, 5 );

   git_oid out;
   int ret = git_tag_annotation_create( &out, *repo, tag_name, *obj, sig, message  );
   git_signature_free( sig );
   if( ret )
   {
      return ltk_push_git_error( L );
   }
   return luagi_push_oid( L, &out );
}
/* not really relevant for a lua context
int luagi_tag_create_frombuffer( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *buffer = luaL_checkstring( L, 2 );
   int force = lua_toboolean( L, 3 );

   git_oid out;
   if( git_tag_create_frombuffer( &out, *repo, buffer, force ) )
   {
      return ltk_push_git_error( L );
   }

   return luagi_push_oid( L, &out );
}
*/
int luagi_tag_create_lightweight( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *tag_name = luaL_checkstring( L, 2 );
   git_object **target = checkobject_at( L, 3 );
   int force = lua_toboolean( L, 4 );

   git_oid oid;
   if( git_tag_create_lightweight( &oid, *repo, tag_name, *target, force ) )
   {
      return ltk_push_git_error( L );
   }
   
   return luagi_push_oid( L, &oid );
}

int luagi_tag_delete( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *tag_name = luaL_checkstring( L, 2 );

   if( git_tag_delete( *repo, tag_name ) )
   {
      ltk_error_abort( L );
   }
   return 0;
}

int luagi_tag_list( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   git_strarray data;
   if( git_tag_list( &data, *repo ) )
   {
      return ltk_push_git_error( L );
   }
   ltk_push_strarray( L, data );
   git_strarray_free( &data );
   return 1;
}
   
int luagi_tag_list_match( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   const char *pattern = luaL_checkstring( L, 2 );

   git_strarray data;
   if( git_tag_list_match( &data, pattern, *repo ) )
   {
      return ltk_push_git_error( L );
   }
   ltk_push_strarray( L, data );
   git_strarray_free( &data );
   return 1;
}

static int foreach_cb( const char *name, git_oid *oid, void *payload )
{
   luagi_foreach_t *p = payload; 
   lua_pushvalue( p->L, p->callback_pos );

   lua_pushstring( p->L, name );
   luagi_push_oid( p->L, oid );

   if( lua_pcall( p->L, 2, 1, 0 ) )
   {
      luaL_error( p->L, "call to tag foreach callback failed" );
      return 1;
   }
   int ret = luaL_checkinteger( p->L, -1 );
   lua_pop( p->L, 1 );
   return ret;
}

int luagi_tag_foreach( lua_State *L )
{
   git_repository **repo = checkrepo( L, 1 );
   luaL_checktype( L, 2, LUA_TFUNCTION );
   luagi_foreach_t *p = malloc( sizeof( luagi_foreach_t ) );
   p->L = L;
   p->callback_pos = 2;
   if( git_tag_foreach( *repo, foreach_cb, p ) )
   {
      ltk_error_abort( L );
   }
   free( p );
   return 0;
}


int luagi_tag_free( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );
   git_tag_free( *tag );
   return 0;
}

int luagi_tag_id( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );

   const git_oid *oid = git_tag_id( *tag );
   return luagi_push_oid( L, oid );
}

int luagi_tag_target( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );
   git_object **target = lua_newuserdata( L, sizeof( git_object * ) );

   if( git_tag_target( target, *tag ) )
   {
      return ltk_push_git_error( L );
   }
   ltk_setmetatable( L, LUAGI_OBJECT_FUNCS );
   return 1;
}

   
int luagi_tag_target_id( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );

   const git_oid *oid = git_tag_target_id( *tag );
   return luagi_push_oid( L, oid );
}

int luagi_tag_target_type( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );

   git_otype type = git_tag_target_type( *tag );
   lua_pushstring( L, luagi_string_from_otype( type ) );
   return 1;
}

int luagi_tag_name( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );
   lua_pushstring( L, git_tag_name( *tag ) );
   return 1;
}

int luagi_tag_tagger( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );
   const git_signature *sig = git_tag_tagger( *tag );
   signature_to_table( L, sig );
   return 1;
}

int luagi_tag_message( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );

   lua_pushstring( L, git_tag_message( *tag ) );
   return 1;
}

int luagi_tag_peel( lua_State *L )
{
   git_tag **tag = checktag_at( L, 1 );
   git_object **object = lua_newuserdata( L, sizeof( git_object * ) );

   if( git_tag_peel( object, *tag ) )
   {
      return ltk_push_git_error( L );
   }
   ltk_setmetatable( L, LUAGI_OBJECT_FUNCS );
   return 1;
}
