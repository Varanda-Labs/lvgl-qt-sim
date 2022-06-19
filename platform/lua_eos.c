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


/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <memory.h>
#include "eos_config.h"
#include "mos.h"

#include "lauxlib.h"
#include "lualib.h"
#include "log.h"
#include "lua_eos.h"
#include "nat_cmd.h"

#ifndef MOS_DESKTOP
  #include "main_defs.h"
#else
  void toConsole(char * msg);
#endif


#define READ_BUF_SIZE 1024

#ifdef USE_DOUG_LEA_MALLOC
  #include "utils/malloc.h"
  mspace gDlmspace;
  static struct mallinfo dlinfo;
#endif

/* The variable used to hold the event queue's data structure. */
static mos_queue_h_t event_queue;

static lua_State * L;

lua_State * get_lua_state(void) {return L;}

void add_event_to_queue( const void * ev_item)
{

  if ( mos_queue_put( event_queue, (const void *) ev_item) != MOS_PASS) {
    LOG_E("timer_callback: event Q is full");
  }

}

void cb_event_push_timer(lua_State *L, ev_queue_item_t * item_ptr)
{
  lua_pushstring(L, "ev_id");                      // Key
  lua_pushinteger(L, EV_SYS_TIMER);   // value
  lua_settable(L, -3);

  lua_pushstring(L, "task_id");                      // Key
  lua_pushinteger(L, item_ptr->item.timer_item.taskID);   // value
  lua_settable(L, -3);

  lua_pushstring(L, "timer_id");                      // Key
  lua_pushinteger(L, item_ptr->item.timer_item.timerID);   // value
  lua_settable(L, -3);
}

static void cb_event_push_text (lua_State *L, ev_queue_item_t * item_ptr)
{
  lua_pushstring(L, "ev_id");                      // Key
  lua_pushinteger(L, item_ptr->event_id);    // value
  lua_settable(L, -3);

  lua_pushstring(L, "arg");                        // Key
  lua_pushstring(L, item_ptr->item.generic_text.text);   // value
  lua_settable(L, -3);
  free(item_ptr->item.generic_text.text);
}

static void cb_event_push_obj (lua_State *L, ev_queue_item_t * item_ptr)
{
  lua_pushstring(L, "ev_id");                      // Key
  lua_pushinteger(L, item_ptr->event_id);    // value
  lua_settable(L, -3);

  lua_pushstring(L, "obj");                        // Key
  lua_pushstring(L, item_ptr->item.generic_obj.obj);   // value
  lua_settable(L, -3);
 }


bool add_text_event(sys_events_t id, char * msg)
{
    unsigned long len = strlen(msg);
    if (len == 0) {
        LOG_W("add_text_event: len = 0");
        return false;
    }

    char * txt = MOS_MALLOC(len + 1);
    if ( ! txt) {
        LOG_E("add_text_event: no memo");
        return false;
    }
    memcpy(txt, msg, len+1);

    ev_queue_item_t ev_item;
    memset(&ev_item, 0, sizeof(ev_item));
    ev_item.event_id = id;
    ev_item.cb_event_push = (void *) cb_event_push_text;
    ev_item.item.generic_text.text = txt;
    add_event_to_queue(&ev_item);

    return true;
}

#define MAX_WAIT_READ_EVENT_Q       MOS_WAIT_FOREVER

static int luac_eos_user_event(lua_State *L)
{
  ev_queue_item_t ev_item;
  memset(&ev_item, 0, sizeof(ev_item));
  ev_item.event_id = EV_SYS_USER_DEF;
  ev_item.cb_event_push = (void *) cb_event_push_obj;
  ev_item.item.generic_obj.obj = 0;
  add_event_to_queue(&ev_item);

  lua_pushboolean(L,1);
  return 1;
}

static int luac_eos_read_event_table(lua_State *L)
{
  int num_items = 0;
  ev_queue_item_t ev_item;
  memset(&ev_item, 0, sizeof(ev_item));
  bool have_table = false;

  while (mos_queue_get( event_queue, &ev_item, MAX_WAIT_READ_EVENT_Q) == MOS_PASS) {
    if (have_table == false) {
        lua_newtable(L);
        have_table = true;
    }
    if (ev_item.cb_event_push == NULL) {
      LOG_E("luac_eos_read_event_table: missing event push callback, event_id = %d", ev_item.event_id);
      return 0;
    }

    lua_pushnumber(L, num_items + 1);
    lua_newtable(L);
    ((cb_event_push_t)(ev_item.cb_event_push))(L, &ev_item);
    lua_settable(L, -3);

    num_items++;
    if (mos_queue_waiting(event_queue) == 0) break;
  }

  if (num_items == 0) { // probably never happen
      LOG_E("luac_eos_read_event_table: unexpected num_items == 0");
      lua_pushnil(L);
  }
  return 1;

}

static void timer_callback(mos_timer_id_t timer_id)
{
  //mos_timer_id_t timer_id = ( uint32_t ) arg;

  ev_queue_item_t ev_item;
  memset(&ev_item, 0, sizeof(ev_item));
  ev_item.event_id = EV_SYS_TIMER;
  ev_item.cb_event_push = cb_event_push_timer;
  ev_item.item.timer_item.taskID = timer_id >> 16;
  ev_item.item.timer_item.timerID = timer_id & 0xffff;
  //LOG("timer_callback: taskID = %d, timerID = %d", ev_item.item.timer_item.taskID, ev_item.item.timer_item.timerID);
  add_event_to_queue(&ev_item);

}


// set timer:
// task ID
// if possible: event queue
// timer ID (where 0 is delay)
// expire in milliseconds
static int luac_eos_set_timer(lua_State *L)
{

  //LOG("luac_eos_set_timer: collecting values from LUA");

  int taskID = (int) lua_tointeger(L,1);
  int timerID = (int) lua_tointeger(L,2);
  int time = (int) lua_tointeger(L,3);

  //LOG("luac_eos_set_timer: taskID = %d, timerID = %d, time = %d", taskID, timerID, time);

  unsigned int _timerID = (unsigned int) (taskID << 16) | (timerID & 0xffff);

  // mos_timer_h_t tm = mos_timer_create_single_shot( time, timer_callback, _timerID);
  bool tm = mos_timer_create_single_shot( time, timer_callback, _timerID);

  if ( ! tm) {
     LOG_E("luac_eos_set_timer: xTimerCreate fail");
  }


  return 0;
}

static int luac_eos_print_str(lua_State *L)
{
  char * s;

  s = (char *) luaL_checkstring(L, 1);
  if (s) {
      toConsole(s);
  }

  return 0;
}


static void register_luacs(lua_State *L)
{
  lua_pushcfunction(L, luac_eos_set_timer);
  lua_setglobal(L, "eos_set_timer");


  lua_pushcfunction(L, luac_eos_user_event);
  lua_setglobal(L, "eos_user_event");

  lua_pushcfunction(L, luac_eos_read_event_table);
  lua_setglobal(L, "eos_read_event_table");

  lua_pushcfunction(L, luac_eos_print_str);
  lua_setglobal(L, "eos_print");


}

void lua_bindings_registration(lua_State *L); // TODO: use header


void luaTask(void * arg)
{
  LOG("luaInit...\r\n");

  if ( (event_queue = mos_queue_create ( EV_QUEUE_LENGTH, sizeof( ev_queue_item_t ))) == NULL) {
    LOG_E("Could not create event_queue");
    return;
  }

  //int status, result;
  L = luaL_newstate();  /* create state */
  if (L == NULL) {
    LOG_E("cannot create state: not enough memory");
    return;
  }

  luaL_openlibs(L);
  register_luacs(L);
  lua_bindings_registration(L);

  int err;

  luaL_loadstring(L, "EOS_PLATFORM = \"" EOS_PLATFORM "\" EOS_VERSION = " EOS_VERSION);
  lua_pcall(L, 0, 0, 0);

  if ((err = luaL_loadfile(L, EOS_APP_FILENAME)) != 0) {
    switch(err) {
    case LUA_ERRFILE:
      LOG_E("loadfile: fail to open %s", EOS_APP_FILENAME);
      break;
    case LUA_ERRSYNTAX: LOG_E("loadfile: syntax error during pre-compilation");
      break;
    case LUA_ERRMEM:
      LOG_E("loadfile: memory allocation error.");
      break;
    default:
      LOG_E("loadfile: unknown error.");
      break;
    }
    return;
  }
  err = lua_pcall(L, 0, 0, 0);
  if (err) {
    LOG_E( "%s", lua_tostring(L, -1));
    lua_pop(L, 1);  /* pop error message from the stack */
  }

#if 1
  if ((err = luaL_loadfile(L, START_LUA_EOS_FILENAME )) != 0) {
      switch(err) {
      case LUA_ERRFILE:
          LOG_E("loadfile: fail to open eos.lua");
          break;
      case LUA_ERRSYNTAX: LOG_E("loadfile: syntax error during pre-compilation");
          break;
      case LUA_ERRMEM:
          LOG_E("loadfile: memory allocation error.");
          break;
      default:
          LOG_E("loadfile: unknown error.");
          break;
      }
      return;
  }

  err = lua_pcall(L, 0, 0, 0);
  if (err) {
    LOG_E( "%s", lua_tostring(L, -1));
    lua_pop(L, 1);  /* pop error message from the stack */
  }
#endif

  LOG_E("lua thread terminated");
}

typedef enum {
    SHELL_MODE__LUA,
    SHELL_MODE__NATIVE
} shell_mode_t;

static shell_mode_t shell_mode = SHELL_MODE__LUA;

void switchNativeShellMode(void)
{
    if (shell_mode == SHELL_MODE__NATIVE) {
        LOG("Already in native shell mode");
        return;
    }
    shell_mode = SHELL_MODE__NATIVE;
    nat_cmd_prompt(true);
}

void sendTextToConsoleController(char * msg)
{
  if (shell_mode == SHELL_MODE__LUA) {
    add_text_event( EV_SYS_TEXT_FROM_CONSOLE, msg);
  }
  else {
    nat_cmd_exec( msg);
  }
}

static bool switchLuaShellMode(const char * line, int num_args, const char ** args)
{
    shell_mode = SHELL_MODE__LUA;
    toConsole("\r\n");
    add_text_event( EV_SYS_TEXT_FROM_CONSOLE, "\r\n");
    return false;
}

static bool show_lua_heap(const char * line, int num_args, const char ** args)
{
    char buf[256];
    dlinfo = mspace_mallinfo(gDlmspace);
    sprintf(buf,
    "lua native heap statistics:\r\n"
    "  Allocated: %d\r\n"  /* total allocated space */
    "  Free:      %d\r\n\r\n",
    dlinfo.uordblks, /* total allocated space */
    dlinfo.fordblks); /* total free space */
    toConsole(buf);

    return true;
}
void eos_init(void)
{
  nat_cmd_init();
  nat_cmd_register("lua", "switch to lua shell", &switchLuaShellMode, MENU_DEV_ACCESS);
#ifdef USE_DOUG_LEA_MALLOC
  void * base = malloc(EOS_LUA_HEAP_SIZE + 10);
  if (! base) {
    while(1)
    {
	   LOG_E("Fail to allocate lua heap\n");
	   mos_thread_sleep(1000);
    }
  }
  gDlmspace = create_mspace_with_base(base, EOS_LUA_HEAP_SIZE, 0);
  nat_cmd_register("lheap", "show lua heap statistics", &show_lua_heap, MENU_DEV_ACCESS);

#endif
  
//  void * ptr;
//  int hsize_ok=0, hsize = 1024;
//  while ( (ptr = mspace_malloc(gDlmspace, hsize))) {
//      printf("dl OK for %d\r\n", hsize);
//      hsize_ok = hsize;
//      hsize *= 2;
//  }
//  while(1)
//  {
//      printf("dl max hsize = %d\r\n", hsize_ok);
//      mos_thread_sleep(1000);
//  }

}
