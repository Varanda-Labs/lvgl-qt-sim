#ifndef TERMDLG_H
#define TERMDLG_H
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

#include <QDialog>
#include "console.h"

namespace Ui {
class TermDlg;
}

class TermDlg : public QDialog
{
  Q_OBJECT

public:
  explicit TermDlg(QWidget *parent = nullptr);
  ~TermDlg();

private:
  Ui::TermDlg *ui;
public:
  Console * m_console;
};

#endif // TERMDLG_H
