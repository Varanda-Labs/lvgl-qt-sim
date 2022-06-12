/****************************************************************************/
//
//  Module:          $URL: $
//  Created By:      Marcelo Varanda
//  Revision:        $Revision: $
//  Last Updated By: $Author: $
//  Last Updated:    $Date:  $
//
//  Description: Part of M-OS 
//
//  Copyright (c) 2021 Marcelo Varanda, all rights reserved.
//
//
/****************************************************************************/

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "mos.h"
#include "mos_desktop_timer.h"


#include <pthread.h>

static mos_mutex_h_t mutex; // mos_mutex_create
static mos_thread_h_t task;

#ifndef UNIT_TEST
  #define STATIC static
#else
  #define STATIC
#endif

#ifdef __cplusplus
extern "C" {
#endif


STATIC uint64_t tick_counter = 0;

STATIC list_entry_t list[NUM_MAX_TIMERS];
STATIC volatile uint32_t list_num_entries = 0;
STATIC volatile list_entry_t * head = NULL;

STATIC list_entry_t * insert( uint64_t expire, timer_func_t callback, mos_timer_id_t id) {
    int i;

    list_entry_t * entry = NULL;

    if (list_num_entries >= NUM_MAX_TIMERS) {
        LOG_E("timer list full");
        return NULL;
    }
    for (i = 0; i < NUM_MAX_TIMERS; i++) {
        if (list[i].state == ST_EMPTY) {
            entry = &list[i];
            break;
        }
    }
    if ( ! entry) {
        LOG_E("unexpected: timer not full but no empty record");
        return NULL;
    }
    entry->state = ST_COUNTING;
    entry->expire = expire;
    entry->callback = callback;
    entry->id = id;
    entry->next = NULL;

    list_num_entries++;

    list_entry_t * ptr = head;
    if ( ! ptr) {
        head = entry;
        return entry;
    }

    if (entry->expire < ptr->expire) {
        entry->next = ptr;
        head = entry;
        return entry;
    }

    while(ptr) {
        if (ptr->next == NULL) {
            ptr->next = entry;
            break;
        }

        if (entry->expire < ptr->next->expire) {
            entry->next = ptr->next;
             ptr->next = entry;
            break;
        }
        ptr = ptr->next;
    }

    return entry;
}

bool mos_timer_create_single_shot( uint32_t time_milliseconds, timer_func_t callback, mos_timer_id_t id )
{
  mos_mutex_lock(mutex);
  if (time_milliseconds == 0) time_milliseconds = 10;
  list_entry_t * entry = insert( tick_counter + MILLISEC_TO_TICK(time_milliseconds),  callback,  id);
  mos_mutex_unlock(mutex);
  if (entry == NULL)
      return false;
  return true;
}

static void timer_thread(void *arg)
{
#ifdef SHOW_TICK
    uint64_t last = 0;
#endif
    timer_func_t        callback;
    mos_timer_id_t      id;

    LOG("Timer therad started");
    while(1) {
        usleep(TICK_PERIOD);

        tick_counter++;


        mos_mutex_lock(mutex);

        list_entry_t  entry;
        list_entry_t  *next;
        list_entry_t  *ptr = head;
        while (ptr) {
            if (ptr->expire <= tick_counter) {
                callback = ptr->callback;
                id = ptr->id;
                next = ptr->next;
                memset(ptr, 0, sizeof(list_entry_t));
                ptr = next;
                head = ptr; // update header
                list_num_entries--;
                mos_mutex_unlock(mutex);
                if (callback) {
                    callback(id);
                }
                mos_mutex_lock(mutex);
                continue;

            }
            if (ptr)
                ptr = ptr->next;
        }

        mos_mutex_unlock(mutex);
#ifdef SHOW_TICK
        if (tick_counter - last > MILLISEC_TO_TICK(1000)) {
            last = tick_counter;
            LOG("tick");
        }
#endif
    }
}

void mos_timer_init(void)
{
    memset (list, 0, sizeof(list));
    mutex = mos_mutex_create();
    task = mos_thread_new( "luaTask", timer_thread, NULL, 1024 * 1024, 10 );

}

#ifdef __cplusplus
}
#endif



