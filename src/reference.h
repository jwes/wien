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
#ifndef IS_LUAGI_REFERENCE
#define IS_LUAGI_REFERENCE
#include <lua.h>
#include <lauxlib.h>

// branch is a reference too but lua checks the metatablename
int luagi_reference_gen_target( lua_State *L, const char *tablename );
int luagi_reference_gen_target_peel( lua_State *L, const char *tablename );
int luagi_reference_gen_symbolic_target( lua_State *L, const char *tablename );
int luagi_reference_gen_type( lua_State *L, const char *tablename );
int luagi_reference_gen_name( lua_State *L, const char *tablename );
int luagi_reference_gen_resolve( lua_State *L, const char *tablename );
int luagi_reference_gen_symbolic_set_target( lua_State *L, const char *tablename );
int luagi_reference_gen_set_target( lua_State *L, const char *tablename );
int luagi_reference_gen_rename( lua_State *L, const char *tablename );
int luagi_reference_gen_delete( lua_State *L, const char *tablename );
int luagi_reference_gen_foreach( lua_State *L, const char *tablename );
int luagi_reference_gen_is_branch( lua_State *L, const char *tablename );
int luagi_reference_gen_is_remote( lua_State *L, const char *tablename );
int luagi_reference_gen_is_tag( lua_State *L, const char *tablename );
int luagi_reference_gen_is_note( lua_State *L, const char *tablename );
int luagi_reference_gen_peel( lua_State *L, const char *tablename );
int luagi_reference_gen_shorthand( lua_State *L, const char *tablename );
int luagi_reference_gen_free( lua_State *L, const char *tablename );

// stub classes called by reference directly
int luagi_reference_lookup( lua_State *L );
int luagi_reference_name_to_id( lua_State *L );
int luagi_reference_dwim( lua_State *L );

int luagi_reference_symbolic_create_matching( lua_State *L );
int luagi_reference_symbolic_create( lua_State *L );
int luagi_reference_create( lua_State *L );
int luagi_reference_create_matching( lua_State *L );

// reference methods
int luagi_reference_target( lua_State *L );
int luagi_reference_target_peel( lua_State *L );
int luagi_reference_symbolic_target( lua_State *L );
int luagi_reference_type( lua_State *L );
int luagi_reference_name( lua_State *L );
int luagi_reference_resolve( lua_State *L );
int luagi_reference_symbolic_set_target( lua_State *L );
int luagi_reference_set_target( lua_State *L );
int luagi_reference_rename( lua_State *L );
int luagi_reference_delete( lua_State *L );
int luagi_reference_remove( lua_State *L );
int luagi_reference_list( lua_State *L );
int luagi_reference_foreach( lua_State *L );
int luagi_reference_is_branch( lua_State *L );
int luagi_reference_is_remote( lua_State *L );
int luagi_reference_is_tag( lua_State *L );
int luagi_reference_is_note( lua_State *L );
int luagi_reference_peel( lua_State *L );
int luagi_reference_shorthand( lua_State *L );
int luagi_reference_free( lua_State *L );

// normal from glob and just names
int luagi_reference_iterator( lua_State *L );
int luagi_reference_iterator_free( lua_State *L );

int luagi_reference_foreach_glob( lua_State *L );
int luagi_reference_has_log( lua_State *L );
int luagi_reference_ensure_log( lua_State *L );
int luagi_reference_normalize_name( lua_State *L );

int luagi_reference_is_valid_name( lua_State *L );

#define LUAGI_REFERENCE_FUNCS "is.luagi.reference"
#define LUAGI_REFERENCE_ITER_FUNCS "is.luagi.reference.iterator"

#define check_ref_at( L, N ) \
   (git_reference **) luaL_checkudata( L, N, LUAGI_REFERENCE_FUNCS )

#define checkreferenceiter_at( L, N ) \
   (git_reference_iterator **) luaL_checkudata( L, N, LUAGI_REFERENCE_ITER_FUNCS )
static const struct luaL_Reg luagi_reference_funcs [] = {
   { "target", luagi_reference_target },
   { "target_peel", luagi_reference_target_peel },
   { "symbolic_target", luagi_reference_symbolic_target },
   { "type", luagi_reference_type },
   { "name", luagi_reference_name },
   { "resolve", luagi_reference_resolve },
   { "set_symbolic_target", luagi_reference_symbolic_set_target },
   { "set_target", luagi_reference_set_target },
   { "rename", luagi_reference_rename },
   { "delete", luagi_reference_delete },
   { "is_branch", luagi_reference_is_branch },
   { "is_remote", luagi_reference_is_remote },
   { "is_tag",  luagi_reference_is_tag },
   { "is_note", luagi_reference_is_note },
   { "peel", luagi_reference_peel },
   { "shorthand", luagi_reference_shorthand },
   { "__gc", luagi_reference_free },
   { NULL, NULL }
};

static const struct luaL_Reg luagi_reference_iter_funcs [] = {
   { "__gc", luagi_reference_iterator_free },
   { NULL, NULL }
};

#endif
