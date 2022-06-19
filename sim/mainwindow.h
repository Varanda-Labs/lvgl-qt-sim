#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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

#include <QMainWindow>
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include "termdlg.h"
#include "eos_init.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage display_image;
    Ui::MainWindow *ui;

private slots:
  void timerEvent(QTimerEvent *event);
  void onMousePressed(int x, int y);
  void onMouseReleased(int x, int y);
  void onMouseMoved(int x, int y);
  void writeDataFromTerm(const QByteArray &data);
  void forwardToConsole(char * msg);


private:
  virtual bool eventFilter(QObject *obj, QEvent *event);

  int timerId;
  TermDlg * m_term;
  Console * m_term_console;
  LuaInit luaInit;

};
#endif // MAINWINDOW_H
