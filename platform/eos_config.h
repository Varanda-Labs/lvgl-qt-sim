#ifndef EOS_CONFIG_H
#define EOS_CONFIG_H
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
#define EOS_VERSION "0.02"

#define MAX_NUM_NATIVE_MENU_ITEMS 32

#ifdef MOS_DESKTOP
  #define ROOT_PATH "../target_files/"
  #define EOS_PLATFORM "SIMULATOR"
#else // cmake defines plat in BOARD_DEF
  #define ROOT_PATH "/spiffs/"
  #define EOS_PLATFORM BOARD_DEF
#endif

#define START_LUA_EOS_FILENAME (ROOT_PATH "eos.lua")
#define EOS_APP_FILENAME (ROOT_PATH "app.lua")

// #ifdef MOS_DESKTOP
//   #define START_LUA_EOS_FILENAME "../target_files/eos.lua"
//   #define EOS_APP_FILENAME "../target_files/app.lua"
//   #define EOS_PLATFORM "SIMULATOR"

// #else // for now assume ESP32
//   #define START_LUA_EOS_FILENAME "/spiffs/eos.lua"
//   #define EOS_APP_FILENAME "/spiffs/app.lua"
//   #define EOS_PLATFORM "ESP32"
// #endif


#define HAS_LVGL // has LVGL

#ifdef HAS_LVGL
  #define SHOW_ANIMATED_SPLASH
  #ifdef MOS_DESKTOP
    //#define MOS_DESKTOP_SPLASH
  #endif
#endif

#define EV_QUEUE_LENGTH    32

#ifdef MOS_DESKTOP
  #define LOWEST_PRIORITY 1 // assume low value has low priority
#else
  #define LOWEST_PRIORITY tskIDLE_PRIORITY
#endif

// Stack sizes
#define LUA_EOS_STACK_SIZE (1024 * 1024) // 1M
#define LVGL_TASK_STACK_SIZE (1024 * 1024) // 1M
#define CONSOLE_INPUT_STACK_SIZE (1024) // 0.5 K 

// lua heap size
#ifndef KALUNGA
  #define EOS_LUA_HEAP_SIZE (2 * 1024 * 1024) // 2MBytes
#else
  #define EOS_LUA_HEAP_SIZE (500 * 1024) // 500K
#endif

// Priorities
#define	LUA_TASK_PRIORITY		( LOWEST_PRIORITY + 1 )
#define	CONSOLE_INPUT_TASK_PRIORITY ( LOWEST_PRIORITY + 2 )
#define	LVGL_TASK_PRIORITY		( LOWEST_PRIORITY + 3 )


//---- native access level
typedef enum {
    MENU_DEV_ACCESS,
    MENU_USER_ACCESS,
} menu_access_t;

#define MENU_ACCESS MENU_DEV_ACCESS
#define SHELL_MAX_LINE_SIZE 256
#define SHELL_MAX_NUM_ARGS 8

#ifdef MACOS
  #define BACKSPACE_CHAR 0x7f
#else
  #define BACKSPACE_CHAR 0x08
#endif

#define SWITCH_SHELL_MODE_CHAR '+'
#define SWITCH_SHELL_MODE_COUNT 3



//-----------------------------------------------------------------
#endif // EOS_CONFIG_H
