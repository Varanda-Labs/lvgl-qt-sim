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
#include <QThread>
#include <QStyle>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lv_conf.h"
#include "lvgl.h"
#include "lvgl_integr.h"
#include "log.h"
#include "eos_init.h"
#include "nat_cmd.h"
//#include "lua_eos.h"
#include "eos_config.h"

extern "C" void eos_init(void);

#define LUA_EOS_VERSION "0.0"

//extern "C" void nat_cmd_init(void);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , display_image(LV_HOR_RES_MAX,LV_VER_RES_MAX, QImage::Format_RGB16)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->lb_display->setMaximumWidth(LV_HOR_RES_MAX);
    ui->lb_display->setMaximumHeight(LV_VER_RES_MAX);
    setWindowTitle("LVGL Qt Simulator - version " LUA_EOS_VERSION);

    setGeometry(0,0, LV_HOR_RES_MAX, LV_VER_RES_MAX);


    gMainObj = this;

    installEventFilter(this);

    connect(ui->lb_display, SIGNAL(mousePressed(int, int)), this, SLOT(onMousePressed(int, int)));
    connect(ui->lb_display, SIGNAL(mouseReleased(int, int)), this, SLOT(onMouseReleased(int, int)));

    // ui->lb_display->setPixmap(display_pixelmap);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //display_image.fill(Qt::green);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //ui->lb_display->update();

#if 0 // disable terminal for now
    m_term = new TermDlg(this);
    m_term_console = m_term->m_console;
    connect(m_term_console, &Console::getData, this, &MainWindow::writeDataFromTerm);
    m_term->show();
    //m_term->setFocus();
#endif

#ifdef HAS_LVGL
    lv_integr_run();
#endif

    timerId = startTimer(LVGL_TICK_TIME);


    connect(&luaInit, &LuaInit::luaToConsole, this, &MainWindow::forwardToConsole);

    //nat_cmd_init();
    //eos_init();

    luaInit.start();

}

void MainWindow::forwardToConsole(char * msg)
{
#if 1
    m_term_console->putString(C_GREEN, msg);
#else
    // debug only
    m_term_console->putHexData((source_msg_t)0, QByteArray((char*)msg, strlen(msg)));
#endif
    free(msg);
}

#ifdef MACOS
  #define BACKSPACE_CHAR 0x7f
#else
  #define BACKSPACE_CHAR 0x08
#endif

#define SWITCH_SHELL_MODE_CHAR '+'
#define SWITCH_SHELL_MODE_COUNT 3

void MainWindow::writeDataFromTerm(const QByteArray &data)
{
    //LOG("writeDataFromTerm: '%s', len=%u", data.toStdString().c_str(), data.length());
    static char msg[1024] = {0};
    static int msg_len = 0;

    if (data.size() == 0) return;

    int to_transfer = data.size();

    if (to_transfer == 1) {
        const char * c = data.data();
        if (*c == BACKSPACE_CHAR) { // note: 0x7f is for Mac
          msg[msg_len] = 0;
          if (msg_len > 1)
              msg_len--;
          return;
        }
    }

    int fit = sizeof(msg) - (msg_len + 1);
    if (to_transfer > fit)
        to_transfer = fit;
    if (to_transfer <= 0) {
        LOG("there is no room for line terminal buffer");
        msg_len = 0;
        memset(msg, 0, sizeof(msg));
        return;
    }
    memcpy(&msg[msg_len], data.data(), to_transfer);
    msg_len += to_transfer;

#if 0
    // scan for native console switch pattern (3 scape characters):
    int esc_n = 0;
    char * ptr = msg;
    while(*ptr) {
        if (*ptr == SWITCH_SHELL_MODE_CHAR) {
            esc_n++;
            if (esc_n >= SWITCH_SHELL_MODE_COUNT) {
                msg_len = 0;
                memset(msg, 0, sizeof(msg));
                switchNativeShellMode();
            }
        }
        else {
            esc_n = 0;
        }
        ptr++;
    }
#endif

    // if last char is either CR or LF we send to console controller
    if (msg[msg_len - 1] != '\r') {
        return;
    }

    // dispatch line to C program
#if 0
    sendTextToConsoleController(msg);
#else
    nat_cmd_exec( msg);
#endif
    msg_len = 0;
    memset(msg, 0, sizeof(msg));
}

static int last_state = LV_INDEV_STATE_REL;

void MainWindow::onMousePressed(int x, int y)
{
    printf("Mouse pressed %d, %d\n", x, y);
    lv_integr_update_pointer(x, y, LV_INDEV_STATE_PR);
    last_state = LV_INDEV_STATE_PR;
}

void MainWindow::onMouseReleased(int x, int y)
{
    printf("Mouse released %d, %d\n", x, y);
    lv_integr_update_pointer(x, y, LV_INDEV_STATE_REL);
    last_state = LV_INDEV_STATE_REL;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
    int x = mouseEvent->pos().x();
    int y = mouseEvent->pos().y();
    printf("Mouse move %d, %d\n", x, y);
    lv_integr_update_pointer(x, y, last_state);
  }
  return false;
}

void MainWindow::onMouseMoved(int x, int y)
{
    printf("Mouse released %d, %d\n", x, y);
    lv_integr_update_pointer(x, y, last_state);
}




void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    lv_integr_timer();
}

MainWindow::~MainWindow()
{
    delete ui;
    killTimer(timerId);
}

