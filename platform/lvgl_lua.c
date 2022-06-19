/***************************************************************
 *
 *                 This code is part of LVGL-Qt-Simulator
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

#include "log.h"
#include "lua_eos.h"
#include "lvgl.h"
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"


#ifdef __cplusplus
extern "C" {
#endif

static void cb_event_push_lvgl (lua_State *L, ev_queue_item_t * item_ptr)
{
  lua_pushstring(L, "ev_id");                      // Key
  lua_pushinteger(L, item_ptr->event_id);    // value
  lua_settable(L, -3);

  //--------- arg table ----------
  lua_pushstring(L, "arg");
  lua_newtable(L);
  // field 1
  lua_pushstring(L, "obj");                      // Key
  lua_pushlightuserdata(L, item_ptr->item.lvgl_item.obj);    // value
  lua_settable(L, -3);

  // field 2
  lua_pushstring(L, "lvgl_event");                        // Key
  lua_pushinteger(L, item_ptr->item.lvgl_item.lv_event);   // value
  lua_settable(L, -3);


  lua_settable(L, -3);
  //-------------------------------

}

static void lv_cb(lv_obj_t * obj, lv_event_t event)
{

    ev_queue_item_t ev_item;
    memset(&ev_item, 0, sizeof(ev_item));
    ev_item.event_id = EV_SYS_LVGL;
    ev_item.cb_event_push = (void *) cb_event_push_lvgl;
    ev_item.item.lvgl_item.obj = obj;
    ev_item.item.lvgl_item.lv_event = event;
    // LOG("add EV_SYS_LVGL event %d", event);
    add_event_to_queue(&ev_item);

}

#define LV_LIB_NAME "lv"
#define LV_OBJECTS  "lv_objs"

// extern void luaL_setfuncs(lua_State *L, void * reg, int v);
// extern void luaL_newlibtable (lua_State *L, void * reg);
// extern void luaL_newlib (lua_State *L, void * reg);

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[])
{
  lua_getglobal(L, LV_LIB_NAME);
  if ( ! lua_istable(L, -1)) {
    // create table to store all lv functions and variables
    luaL_newlib (L, reg);
    //luaL_newlibtable(L,reg); luaL_setfuncs(L,reg,0);
    lua_setglobal(L, LV_LIB_NAME);

    return;
  }
  luaL_setfuncs(L, reg, 0);
}

extern lua_State * get_lua_state(void);

void lv_append_obj(void * obj)
{
  lua_State * L = get_lua_state();
  if ( ! L) {
      return;
  }

  lua_getglobal(L, LV_OBJECTS);

  if ( ! lua_istable(L, -1)) {
    // create a table to track objects to forward events
    lua_newtable(L);
    lua_pushstring(L, "dummy_key");
    lua_pushstring(L, "dummy_val");
    lua_settable(L, -3);
    lua_setglobal(L, LV_OBJECTS);
    lua_getglobal(L, LV_OBJECTS); // to top again
  }

  lua_pushstring(L, "dummy");
  lua_setfield( L, -2, obj );
}

static int bind_lv_obj_set_event_cb (lua_State *L)
{
    void * obj = lua_touserdata(L,1);
    lv_obj_set_event_cb(obj, lv_cb);
    return 0;
}

void lvgl_lua_init(lua_State *L)
{
    lua_pushcfunction(L, bind_lv_obj_set_event_cb);
    lua_setglobal(L, "bind_lv_obj_set_event_cb");
}


#ifdef __cplusplus
  }
#endif



