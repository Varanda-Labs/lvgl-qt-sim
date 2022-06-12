#ifndef __NAT_CMD_H__
#define __NAT_CMD_H__
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

#include "lua.h"
#include "stdbool.h"
#include "eos_config.h"

// following is the prototype for menu callbacks
// if the function returns true the native prompt is sent to console
typedef bool (*menu_func_t)(const char * line, int num_args, const char ** args);

void nat_cmd_init(void);
void nat_cmd_exec(char * line);
void nat_cmd_prompt(bool first);
void nat_cmd_register(const char * name, const char * help, menu_func_t func, menu_access_t access);


//---------------------------------
#endif //__NAT_CMD_H__
