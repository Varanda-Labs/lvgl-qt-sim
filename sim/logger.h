#ifndef LOG_H
#define LOG_H
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

// commit 4 from test

#include <stdio.h>
#if 1
#define LOG         qDebugC
#define LOG_E       qDebugC
#define LOG_I       qDebugC
#define LOG_W       qDebugC
#else
#define LOG(...)         do {/* dummy */} while(0)
#define LOG_E(...)       do {/* dummy */} while(0)
#define LOG_I (...)       do {/* dummy */} while(0)
#define LOG_W(...)       do {/* dummy */} while(0)
#endif


#ifdef __cplusplus
  extern "C" {
#endif


  void qDebugC(const char * format,...);


#ifdef __cplusplus
}
#endif




#endif // LOG_H
