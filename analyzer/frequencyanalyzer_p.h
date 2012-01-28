#ifndef FREQUENCYANALYZER_P_H
#define FREQUENCYANALYZER_P_H
#include "frequencyanalyzer.h"
#include "measureFreqXcorr.h"

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioFormat>

#include <QDebug>
#include <QDataStream>

static const int frameSize = 8192;
static const int sampleSize = 8192/sizeof(int32_T)*sizeof(int);

class FrequencyAnalyzer;
class FrequencyAnalyzerPrivate
{
    Q_DECLARE_PUBLIC(FrequencyAnalyzer)
public:
    FrequencyAnalyzerPrivate(FrequencyAnalyzer *q) : q_ptr(q), input(0),
        device(0), frequency(0), sampling(-1) {}
    ~FrequencyAnalyzerPrivate() {}

    FrequencyAnalyzer *q_ptr;
    QAudioInput *input;
    QIODevice *device;
    QByteArray buffer;
    real32_T frequency;
    int32_T sampling;

    void _q_onReadyRead()
    {
        buffer.append(device->readAll());
        if (buffer.count() >= sampleSize) {
            //TODO optimize me
            //int32_T s[frameSize];
            //QDataStream stream(buffer);
            //for (int i = 0; i!= frameSize; i++)
            //    stream >> s[i];

            int32_T *s = reinterpret_cast<int32_T*>(buffer.data()); //fast black magic

            real32_T snr;
            creal32_T w[frameSize];
            measureFreqXcorr(s, sampling, &frequency, &snr, w);
            qDebug() << buffer.count() << frequency << snr;

            emit q_func()->currentFrequencyChanged(frequency);
            buffer.clear();
        }
    }

    void _q_onStateChanged()
    {
        emit q_func()->stateChanged(static_cast<FrequencyAnalyzer::State>(input->state()));
    }

    void _q_onDeviceDestroyed(QObject*)
    {
        device = 0;
    }
};

#endif // FREQUENCYANALYZER_P_H
