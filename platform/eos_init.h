#ifndef __EOS_INIT_H__
#define __EOS_INIT_H__
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
#include <QObject>
#include <QThread>

QThread * luaCppInit(void);

class LuaInit : public QObject
{
    Q_OBJECT

public:
    LuaInit();

    void start( void );
    void sendToConsole(char * txt);

//public slots:
//    void luaToConsole(char * msg);

signals:
    void luaToConsole(char * msg);

private:
    QThread *  thread;
};







//-----------------------------------------------------
#endif // __EOS_INIT_H__
