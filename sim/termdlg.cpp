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

#include "termdlg.h"
#include "ui_termdlg.h"

TermDlg::TermDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TermDlg)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog);

  Qt::WindowFlags flags = windowFlags();
  //flags |= Qt::WindowMaximizeButtonHint;
  //flags |= Qt::WindowContextHelpButtonHint;
  flags &= ~Qt::WindowContextHelpButtonHint;
  //setWindowFlags(flags);

  m_console = new Console();
  m_console->setMode(MODE_TERMINAL);

  ui->verticalLayout_2->addWidget(m_console);

}

TermDlg::~TermDlg()
{
  delete ui;
}
