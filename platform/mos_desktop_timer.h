#ifndef __MOS_DESK_TIMER_H__
#define __MOS_DESK_TIMER_H__
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
#include <stdint.h>
#include <stdbool.h>
#include "mos.h"

#define NUM_MAX_TIMERS 10
#define TICK_PERIOD 20000  // microseconds (20 milliseconds, 50Hz)... 994 days to roll to zero for uint32_t
#define MILLISEC_TO_TICK(m) (m/20)

typedef enum {
    ST_EMPTY = 0,
    ST_COUNTING,
    ST_EXPIRED,
    ST_IDLE,
} state_t;

typedef struct list_entry_st {
    struct list_entry_st *   next;
    state_t             state;

    uint64_t            expire;
    timer_func_t        callback;
    mos_timer_id_t      id;

} list_entry_t;



#ifdef __cplusplus
extern "C" {
#endif

void mos_timer_init(void);


#ifdef __cplusplus
}
#endif

//----------------------------
#endif
