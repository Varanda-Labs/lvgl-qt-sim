/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
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

#include "Generator.h"

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <QVBoxLayout>
#include <qmath.h>
#include <qendian.h>

#define USE_FILE
#define SAMPLES_FILENAME "/Users/mvaranda/lvgl-qt-sim/app/GuitarPedals/design/guitar_samples.raw"
#define SAMPLE_RATE 44100
#define FRAME_DURATION_MS 5 // 5 milliseconds

Generator::Generator(const QAudioFormat &format
    , qint64 durationUs
    , int sampleRate)
{
    if (format.isValid())
        generateData(format, durationUs, sampleRate);
}

void Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Generator::stop()
{
    m_pos = 0;
    close();
}

void Generator::generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate)
{
#ifdef USE_FILE
    FILE * f = fopen(SAMPLES_FILENAME, "rb");
    if (!f) {
        qDebug("File not found");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    qint64 length = ftell(f);
    fseek(f, 0, SEEK_SET);
    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int n, nread = 0;
    while ((n = fread((ptr + nread), 1, length - nread, f)) > 0) {
        nread += n;
    }
    if (nread != length) {
        qDebug("Read Error read %d, len = %d", nread, length);
        exit(1);
    }


}

qint64 Generator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    //qDebug("readData len = %d\n", len);
    if (!m_buffer.isEmpty()) {
        while (len - total > 0) {
            const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
            memcpy(data + total, m_buffer.constData() + m_pos, chunk);
            m_pos = (m_pos + chunk) % m_buffer.size();
            total += chunk;
        }
    }
    process_audio_frame(data, (int) total);
    return total;
}

qint64 Generator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 Generator::bytesAvailable() const
{
    return m_buffer.size() + QIODevice::bytesAvailable();
}


AudioTest::AudioTest()
    : m_pushTimer(new QTimer(this))
{
    //initializeWindow();
    initializeAudio(QAudioDeviceInfo::defaultOutputDevice());
}

AudioTest::~AudioTest()
{
    m_pushTimer->stop();
}

void AudioTest::initializeWindow()
{
    const QAudioDeviceInfo &defaultDeviceInfo = QAudioDeviceInfo::defaultOutputDevice();
}

void AudioTest::initializeAudio(const QAudioDeviceInfo &deviceInfo)
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    if (!deviceInfo.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = deviceInfo.nearestFormat(format);
    }

    m_generator.reset(new Generator(format, FRAME_DURATION_MS * 1000, SAMPLE_RATE));

    m_audioOutput.reset(new QAudioOutput(deviceInfo, format));
    m_generator->start();

    qreal initialVolume = QAudio::convertVolume(m_audioOutput->volume(),
                                                QAudio::LinearVolumeScale,
                                                QAudio::LogarithmicVolumeScale);
    //m_volumeSlider->setValue(qRound(initialVolume * 100));
    toggleMode();
}

void AudioTest::deviceChanged(int index)
{
    m_generator->stop();
    m_audioOutput->stop();
    m_audioOutput->disconnect(this);
//    initializeAudio(m_deviceBox->itemData(index).value<QAudioDeviceInfo>());
}

void AudioTest::volumeChanged(int value)
{
    qreal linearVolume = QAudio::convertVolume(value / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    m_audioOutput->setVolume(linearVolume);
}

void AudioTest::toggleMode()
{
    m_pushTimer->stop();
    m_audioOutput->stop();
    toggleSuspendResume();

    if (m_pullMode) {
        //switch to pull mode (QAudioOutput pulls from Generator as needed)
//        m_modeButton->setText(tr("Enable push mode"));
        m_audioOutput->start(m_generator.data());
    } else {
        //switch to push mode (periodically push to QAudioOutput using a timer)
//        m_modeButton->setText(tr("Enable pull mode"));
        auto io = m_audioOutput->start();
        m_pushTimer->disconnect();

        connect(m_pushTimer, &QTimer::timeout, [this, io]() {
            if (m_audioOutput->state() == QAudio::StoppedState)
                return;

            QByteArray buffer(32768, 0);
            int chunks = m_audioOutput->bytesFree() / m_audioOutput->periodSize();
            while (chunks) {
               const qint64 len = m_generator->read(buffer.data(), m_audioOutput->periodSize());
               if (len)
                   io->write(buffer.data(), len);
               if (len != m_audioOutput->periodSize())
                   break;
               --chunks;
            }
        });

        m_pushTimer->start(20);
    }

    m_pullMode = !m_pullMode;
}

void AudioTest::toggleSuspendResume()
{
    if (m_audioOutput->state() == QAudio::SuspendedState || m_audioOutput->state() == QAudio::StoppedState) {
        m_audioOutput->resume();
        //m_suspendResumeButton->setText(tr("Suspend recording"));
    } else if (m_audioOutput->state() == QAudio::ActiveState) {
        m_audioOutput->suspend();
       // m_suspendResumeButton->setText(tr("Resume playback"));
    } else if (m_audioOutput->state() == QAudio::IdleState) {
        // no-op
    }
}

void AudioTest::Start()
{
    m_generator->start();
}

void AudioTest::Stop()
{
    m_generator->stop();
}

static AudioTest * AudioTestInstance = NULL;

AudioTest * AudioTest::CreateAudioTestInstance() {
    AudioTestInstance = new AudioTest();
//    AudioTestInstance->Stop();
    return AudioTestInstance;
}

extern "C" {

void start_player()
{
    AudioTestInstance->Start();
}

void stop_player()
{
    AudioTestInstance->Stop();
}

//void process_audio_frame(char * buffer, int len)
//{
//}

}
#endif
