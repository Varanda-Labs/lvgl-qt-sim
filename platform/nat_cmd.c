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
#include "nat_cmd.h"
#include "eos_config.h"
#include <string.h>

extern void toConsole(char * msg);

#define PROMPT "nat> "

typedef struct menu_items_st {
    const char * name;
    const char * help;
    menu_func_t func;
    menu_access_t access;
} menu_items_t;

static menu_items_t menu_items[MAX_NUM_NATIVE_MENU_ITEMS];
static int num_items = 0;
static menu_access_t menu_access = MENU_ACCESS;

void nat_cmd_register(const char * name, const char * help, menu_func_t func, menu_access_t access)
{
    if (num_items >= MAX_NUM_NATIVE_MENU_ITEMS) {
        LOG_E("nat_cmd_register: no room, need to increase MAX_NUM_NATIVE_MENU_ITEMS in eos_config.h");
        return;
    }
    menu_items_t * m = &menu_items[num_items];
    num_items++;
    m->name = name;
    m->help = help;
    m->func = func;
    m->access = access;
}

static char cmd_line[SHELL_MAX_LINE_SIZE];
static char * cmd_args[SHELL_MAX_NUM_ARGS];

void nat_cmd_exec(char * line)
{
    int i, n = 0;
    char * ptr = cmd_line;
    strncpy(cmd_line, line, SHELL_MAX_LINE_SIZE-1);
    cmd_line[SHELL_MAX_LINE_SIZE-1] = 0; // make sure we have a terminator.

    while(*ptr && *ptr != '\r' && *ptr != '\n') {
        if (*ptr == ' ') {
            ptr++;
            continue;
        }
        if (n >= SHELL_MAX_NUM_ARGS) {
            sprintf(cmd_line, "Too many args, max = %d\r\n\r\n", SHELL_MAX_NUM_ARGS);
            toConsole(cmd_line);
            nat_cmd_prompt(false);
            return;
        }
        cmd_args[n++] = ptr;
        // scan for space
        while(*ptr && *ptr != '\r' && *ptr != '\n') {
            if (*ptr == ' ') {
                *ptr = 0; // add a NULL terminator for the arg
                ptr++;
                break;
            }
            ptr++;
        }

    }
    *ptr = 0;

    if (n == 0) {
        //toConsole("empty command\r\n");
        nat_cmd_prompt(false);
        return;
    }

    menu_items_t * m;// = &menu_items[num_items];
    for (i=0; i<num_items; i++) {
        m = &menu_items[i];
        if (strcmp(m->name, cmd_args[0]) == 0) {
            if (m->func) {
                if (m->func(line, n, cmd_args))
                    nat_cmd_prompt(false);
                return;
            }
        }
    }

    toConsole("Unknown command\r\n\r\n");

    nat_cmd_prompt(false);
}

void nat_cmd_prompt(bool first)
{
    if (first)
        toConsole("\r\n" PROMPT);
    else
        toConsole(PROMPT);
}

static bool mn_help(const char * line, int num_args, const char ** args)
{
  int i;
  menu_items_t * m;
  toConsole("\r\nMenu options:\r\n");
  for (i=0; i<num_items; i++) {
      m =  &menu_items[i];
      if (m->access >= menu_access) {
          toConsole("  ");
          toConsole(m->name);
          if (strlen(m->name) > 5) //7)
              toConsole("\t");
          else
              toConsole("\t\t");
          toConsole(m->help);
          toConsole("\r\n");
      }
  }
  toConsole("\r\n");

#if 0
  char buf[128];
  sprintf(buf, "num_args = %d\r\n", num_args);
  toConsole(buf);
  for (i=1; i < num_args;i++) {
      sprintf(buf, "arg[%d] = \"%s\"\r\n", i, args[i]);
      toConsole(buf);
  }
#endif
  return true;

}

void nat_cmd_init(void)
{
  nat_cmd_register("help", "list menu items", &mn_help, MENU_DEV_ACCESS);
  nat_cmd_register("?", "same than help: list menu items", &mn_help, MENU_DEV_ACCESS);

}

