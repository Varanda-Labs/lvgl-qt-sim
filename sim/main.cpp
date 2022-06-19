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

#include <QApplication>

char * args[] = {
    (char *) "x = 5",
    (char *) "print(\"hello Marcelo\")",
    (char *) "print(\"LUA is working\")",
    (char *) "print(x * 2)",

    (char *) NULL
};

extern "C" {
    extern int lua_main (int argc, char **argv);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //printf("lua_main return: %d\n", lua_main(2, args));

    return a.exec();
}
