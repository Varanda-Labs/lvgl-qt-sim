#ifndef GENERATOR_H
#define GENERATOR_H


#include <math.h>

#include <QAudioOutput>
#include <QByteArray>
#include <QComboBox>
#include <QIODevice>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QScopedPointer>

class Generator : public QIODevice
{
    Q_OBJECT

public:
    Generator(const QAudioFormat &format, qint64 durationUs, int sampleRate);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 m_pos = 0;
    QByteArray m_buffer;
};

class AudioTest : QObject //public QMainWindow
{
    Q_OBJECT

public:
    AudioTest();
    ~AudioTest();
    void Start();
    void Stop();

private:
    void initializeWindow();
    void initializeAudio(const QAudioDeviceInfo &deviceInfo);

private:
    QTimer *m_pushTimer = nullptr;

    // Owned by layout
//    QPushButton *m_modeButton = nullptr;
//    QPushButton *m_suspendResumeButton = nullptr;
//    QComboBox *m_deviceBox = nullptr;
//    QLabel *m_volumeLabel = nullptr;
//    QSlider *m_volumeSlider = nullptr;

    QScopedPointer<Generator> m_generator;
    QScopedPointer<QAudioOutput> m_audioOutput;

    bool m_pullMode = true;

private slots:
    void toggleMode();
    void toggleSuspendResume();
    void deviceChanged(int index);
    void volumeChanged(int);
};

#endif // GENERATOR_H
