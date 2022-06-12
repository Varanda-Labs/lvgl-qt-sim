/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "console.h"
#include "log.h"
#include <QScrollBar>
#include <QDebug>
#include <QMenu>

#define FONT_SIZE 18
#define FONT "Courier" //"Courier New"

static QStringList htmlColor =
{
    "Green",
    "Yellow",
    "Blue",
    "LightBlue",
    "Red",
    "Purple",
    "Cyan",
    "Orange",
    "Lime",
};

#define VALS_PER_LINE       16
void Console::hexDump(QByteArray data, QString &out)
{
    out.clear();
    int offset = 0;
    while (data.length() > 0)
    {
        out += QString("  0x%1 ").arg(offset, 4, 16, QLatin1Char('0'));
        QByteArray t = data.left(VALS_PER_LINE);
        out += t.toHex(' ') + QString("   ").repeated(VALS_PER_LINE - t.length()) + "  ";
        for (auto c : t)
        {
            out += isprint(c) ? c : '.';
        }

        out += "\n";
        data.remove(0, t.length());
        offset += VALS_PER_LINE;
    }
}


Console::Console(QWidget *parent) :
    QPlainTextEdit(parent),
    m_localEchoEnabled(false),
    colorIdx(0),
    mode(MODE_TERMINAL)
{
    QPalette p_green;
    p_green = palette();
    p_green.setColor(QPalette::Base, Qt::black);
    p_green.setColor(QPalette::Text, Qt::green);
    setPalette(p_green);

    QTextDocument *doc = document();
    QFont font(FONT, FONT_SIZE);
    doc->setDefaultFont(font);
    setReadOnly(false);
    setUndoRedoEnabled(false);
}

Console::~Console()
{
    stopLogging();
}

void Console::setMode(instance_mode_t m)
{
  mode = m;
  if (m == MODE_TERMINAL) {
    m_localEchoEnabled = true;
  }
}

void Console::startLogging(QString filename)
{
    // Stop old logging
    stopLogging();

    LOG("Start console logging to: %s", filename.toLocal8Bit().data());
    m_logFile.setFileName(filename);
    m_logFile.open(QIODevice::WriteOnly);
}

void Console::stopLogging(void)
{
    if (m_logFile.isOpen())
    {
        LOG("Stop console logging");
        m_logFile.close();
    }
}

void Console::putData(QString &data)
{
  if (mode == MODE_MONITOR) {
    QString plainText = QString(data).toHtmlEscaped();

    blockSignals(true);
    QString s("<p style=\"color:");
    s += htmlColor[colorIdx] + ";white-space:pre\">" + plainText + "</p>";
    appendHtml(s);
    blockSignals(false);
  }
  else {
    moveCursor (QTextCursor::End);
    insertPlainText(data);
    if (m_logFile.isOpen())
    {
        m_logFile.write(data.toLocal8Bit());
        m_logFile.flush();
    }
  }
  QScrollBar *bar = verticalScrollBar();
  bar->setValue(bar->maximum());
}

void Console::putString(c_color_t color, const char * str)
{
  colorIdx = color;
  QString s(str);
  putData(s);
}

void Console::putString(c_color_t color, QString &str)
{
  colorIdx = color;
  putData(str);
}

void Console::putHexData(source_msg_t source, const QByteArray &data)
{
    QStringList tags = {"ToCam", "FromCam", "Unknown"};
    c_color_t color;
    int tag_idx = 0;
    switch(source) {
    case OUTGOING_TO_CAMERA:
      color = C_LIME;
      tag_idx = 0;
      break;
    case INCOMING_FROM_CAMERA:
      color = C_YELLOW;
      tag_idx = 1;
      break;
    default:
      tag_idx = 2;
    }

    QString lines(tags.at(tag_idx) + "\n");
    putString(color, lines);

    hexDump(data, lines);
    putString(color, lines);
}

void Console::setLocalEchoEnabled(bool set)
{
    m_localEchoEnabled = set;
}
#include <QApplication>
#include <QClipboard>

void Console::keyPressEvent(QKeyEvent *e)
{
    // Ignore cut/past key sequences.
    if (e->matches(QKeySequence::Paste))
    {
        LOG("Paste called");
        QClipboard * clipboard = QApplication::clipboard();
        QString t = clipboard->text(QClipboard::Clipboard);
        putData(t);
        emit getData(t.toLocal8Bit());

        return;
    }

    if (e->matches(QKeySequence::Cut) ) {
        return;
    }


#if 0
    if (e->text().length() > 0)
    {
        qDebug() << "Key text: " << e->text().toLatin1().toHex();
    }
    else
    {
        qDebug() << "Key code: " << e->key();
    }
#endif

    // Pass keys that can be used to navigate the console history.
    switch (e->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Home:
    case Qt::Key_End:
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
    case Qt::Key_Shift:
    //case Qt::Key_Backspace:
        QPlainTextEdit::keyPressEvent(e);
        return;
    }

    // Check if a terminal
    if (mode == MODE_TERMINAL)
    {
        if (m_localEchoEnabled)
        {
            // Make sure cursor at the end before passing the key.  Also kills the selection.
            moveCursor(QTextCursor::End);
            QPlainTextEdit::keyPressEvent(e);
        }

        // Send the key to the console controller
        emit getData(e->text().toLocal8Bit());
    }
}

// Disable dropping files onto consoles.
void Console::insertFromMimeData(const QMimeData *source)
{
    Q_UNUSED(source);
}


// Hide context menu entries which edit the text window.
void Console::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *m = createStandardContextMenu();
    QList<QAction *> menuActions = m->actions();
    for (QAction * action : menuActions)
    {
        if ((action->text().contains("Ctrl+X")) ||
            (action->text().contains("Ctrl+V")) ||
            (action->text().contains("Undo")) ||
            (action->text().contains("Redo")) ||
            (action->text().contains("Delete")))
        {
            action->setVisible(false);
        }
    }
    m->exec(event->globalPos());
}

// Override focusOutEvent() so that selections are cleared when leaving the window.
void Console::focusOutEvent(QFocusEvent *e)
{
    // Only clear the selection if it is not a popup.
    if (e->reason() != Qt::PopupFocusReason)
    {
        moveCursor(QTextCursor::End);
    }
    QWidget::focusOutEvent(e);
}
