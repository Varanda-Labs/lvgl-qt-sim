/***************************************************************
 *
 *                 This code is part of LUA_EOS
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

//#include <QThread>
#include "eos_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <QDir>
#include <string.h>
#include "log.h"
#include "mos.h"

QThread * luaCppInit(void);

static LuaInit * luaInitObjtPtr;

LuaInit::LuaInit() {
  luaInitObjtPtr = this;
}

void LuaInit::start( void )
{
    thread = luaCppInit();
}

void LuaInit::sendToConsole(char * msg)
{
    size_t len = strlen(msg);
    if (len == 0) {
        LOG_W("sendToConsole: len = 0");
        return;
    }
    len; // add room for the zero terminator
    char * buf = (char *) malloc(len + 2);
    if (buf == NULL) {
        LOG_E("sendToConsole: no memo");
        return;
    }
    memcpy(buf, msg, len);
#if 1
    buf[len] = 0;
#else
    buf[len] = '\n';
    buf[len + 1] = 0;
#endif
    emit luaToConsole(buf);
}

//static QThread *thread;


extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "log.h"
#include "mos.h"
#include "lua_eos.h"
#include "mos_desktop_timer.h"

extern void rtos_entry(void);

void toConsole(char * msg)
{
    luaInitObjtPtr->sendToConsole(msg);
}

};

static void luaCppThread(void)
{
    QDir dir; LOG("dir: %s", dir.absolutePath().toStdString().c_str());


#ifdef MOS_DESKTOP
    mos_timer_init();
    mos_thread_h_t task = mos_thread_new( "luaTask", luaTask, NULL, LUA_EOS_STACK_SIZE, LUA_TASK_PRIORITY );

#else
    rtos_entry();
#endif
}

QThread * luaCppInit(void)
{
    QThread * thread = QThread::create([]{ luaCppThread(); });
    thread->setStackSize(1024 * 1024);
    LOG("Stack size = %d", thread->stackSize());

    thread->start();
    return thread;
}

