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
#ifndef IS_LUAGI_REMOTE
#define IS_LUAGI_REMOTE

#include <lauxlib.h>
#include <lua.h>

int luagi_remote_list( lua_State *L );
int luagi_remote_lookup( lua_State *L );
int luagi_remote_create( lua_State *L );
int luagi_remote_save( lua_State *L );
int luagi_remote_name( lua_State *L );
int luagi_remote_url( lua_State *L );
int luagi_remote_pushurl( lua_State *L );
int luagi_remote_set_url( lua_State *L );
int luagi_remote_set_pushurl( lua_State *L );
int luagi_remote_add_fetch( lua_State *L );
int luagi_remote_get_fetch_refspecs( lua_State *L );
int luagi_remote_set_fetch_refspecs( lua_State *L );
int luagi_remote_add_push( lua_State *L );
int luagi_remote_get_push_refspecs( lua_State *L );
int luagi_remote_set_push_refspecs( lua_State *L );
int luagi_remote_clear_refspecs( lua_State *L );
int luagi_remote_refspec_count( lua_State *L );
int luagi_remote_get_refspec( lua_State *L );
int luagi_remote_connect( lua_State *L );
int luagi_remote_ls( lua_State *L );
int luagi_remote_download( lua_State *L );
int luagi_remote_fetch( lua_State *L );
int luagi_remote_connected( lua_State *L );
int luagi_remote_stop( lua_State *L );
int luagi_remote_disconnect( lua_State *L );
int luagi_remote_free( lua_State *L );
int luagi_remote_check_cert( lua_State *L );
int luagi_remote_set_transport_from_url( lua_State *L );
int luagi_remote_set_transport_dummy( lua_State *L );
int luagi_remote_set_transport_local( lua_State *L );
int luagi_remote_set_transport_smart( lua_State *L );
int luagi_remote_set_callbacks( lua_State *L );
int luagi_remote_stats( lua_State *L );
int luagi_remote_autotag( lua_State *L );
int luagi_remote_set_autotag( lua_State *L );
int luagi_remote_rename( lua_State *L );
int luagi_remote_update_fetch_head( lua_State *L );
int luagi_remote_set_update_fetch_head( lua_State *L );
int luagi_remote_update_tips( lua_State *L );
int luagi_remote_is_valid_name( lua_State *L );
int luagi_remote_prune( lua_State *L );
int luagi_remote_prune_refs( lua_State *L );
int luagi_remote_upload( lua_State *L );
int luagi_remote_update_tips( lua_State *L );
int luagi_remote_push( lua_State *L );
int luagi_remote_delete( lua_State *L );

static const struct luaL_Reg luagi_remote_funcs [] = {
   { "save",                        luagi_remote_save                    },
   { "name",                        luagi_remote_name                    },
   { "url",                         luagi_remote_url                     },
   { "pushurl",                     luagi_remote_pushurl                 },
   { "set_url",                     luagi_remote_set_url                 },
   { "set_pushurl",                 luagi_remote_set_pushurl             },
   { "add_fetch",                   luagi_remote_add_fetch               },
   { "get_fetch_refspecs",          luagi_remote_get_fetch_refspecs      },
   { "set_fetch_refspecs",          luagi_remote_set_fetch_refspecs      },
   { "add_push",                    luagi_remote_add_push                },
   { "get_push_refspecs",           luagi_remote_get_push_refspecs       },
   { "set_push_refspecs",           luagi_remote_set_push_refspecs       },
   { "clear_refspecs",              luagi_remote_clear_refspecs          },
   { "refspec_count",               luagi_remote_refspec_count           },
   { "get_refspec",                 luagi_remote_get_refspec             },
   { "connect",                     luagi_remote_connect                 },
   { "ls",                          luagi_remote_ls                      },
   { "download",                    luagi_remote_download                },
   { "fetch",                       luagi_remote_fetch                   },
   { "is_connected",                luagi_remote_connected               },
   { "stop",                        luagi_remote_stop                    },
   { "disconnect",                  luagi_remote_disconnect              },
   { "__gc",                        luagi_remote_free                    },
   /*
   { "set_transport_from_url",      luagi_remote_set_transport_from_url  },
   { "set_dummy_transport",         luagi_remote_set_transport_dummy     },
   { "set_local_transport",         luagi_remote_set_transport_local     },
   { "set_smart_transport",         luagi_remote_set_transport_smart     },
   */
   { "set_callbacks",               luagi_remote_set_callbacks           },
   { "stats",                       luagi_remote_stats                   },
   { "autotag",                     luagi_remote_autotag                 },
   { "set_autotag",                 luagi_remote_set_autotag             },
   { "fetch_head",                  luagi_remote_update_fetch_head       },
   { "set_fetch_head",              luagi_remote_set_update_fetch_head   },
   { "update_tips",                 luagi_remote_update_tips             },
   { "prune",                       luagi_remote_prune                   },
   { "prune_refs",                  luagi_remote_prune_refs              },
   { "upload",                      luagi_remote_upload                  },
   { "update_tips",                 luagi_remote_update_tips             },
   { "push",                        luagi_remote_push                    },
   //TODO
   { NULL,                          NULL                                 },
};
#endif
