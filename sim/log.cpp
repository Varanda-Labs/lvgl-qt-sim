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

#include <QDebug>
#include "log.h"

static void qDebugCpp(const char * s) // format,...)
{
//  va_list args;
//  va_start(args, format);
//  qDebug(format, args);
//  va_end(args);
  qDebug("%s", s);
}

extern "C" {
  void qDebugC(const char * format,...)
  {
    char s[1024];
    va_list args;
    va_start(args, format);
    vsprintf (s, format, args );
    qDebugCpp(s); //format, args);
    va_end(args);
  }
}
