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
static const int sampleSize = 8192/sizeof(real_T)*sizeof(uint);

class FrequencyAnalyzer;
class FrequencyAnalyzerPrivate
{
	Q_DECLARE_PUBLIC(FrequencyAnalyzer)
public:
    FrequencyAnalyzerPrivate(FrequencyAnalyzer *q) : q_ptr(q), input(0), device(0), sampling(-1) {}
	~FrequencyAnalyzerPrivate() {}

	FrequencyAnalyzer *q_ptr;
	QAudioInput *input;
    QIODevice *device;
    QByteArray buffer;
    real_T frequency;
    real_T sampling;

    void _q_onReadyRead()
	{
        buffer.append(device->readAll());
        if (buffer.count() >= sampleSize) {
            qDebug() << "Received full fft frame with size " << buffer.count() << ". Processing...";

            //QByteArray ref = buffer.left(); //black magic((
            //real_T *s = reinterpret_cast<real_T*>(ref.data());

            //TODO optimize me
            real_T s[frameSize];
            QDataStream stream(buffer);
            for (int i = 0; i!= frameSize; i++)
                stream >> s[i];

            real_T snr;
            creal_T w[frameSize];
            measureFreqXcorr(s, sampling, &frequency, &snr, w);
            buffer.clear();
        }
	}
};

#endif // FREQUENCYANALYZER_P_H
