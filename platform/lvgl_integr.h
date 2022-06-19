#ifndef __LVGL_INTEGR_H__
#define __LVGL_INTEGR_H__
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

#include "mainwindow.h"

#define LVGL_TICK_TIME 10 // 10 milliseconds

extern MainWindow * gMainObj;

#ifdef __cplusplus
extern "C" {
#endif

void lv_integr_run(void);
void lv_integr_timer(void);
void lv_integr_update_pointer(int x, int y, int state);

#ifdef __cplusplus
};
#endif

//--------------------------------------------------------
#endif // __LVGL_INTEGR_H__



