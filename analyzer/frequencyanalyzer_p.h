#ifndef FREQUENCYANALYZER_P_H
#define FREQUENCYANALYZER_P_H
#include "frequencyanalyzer.h"

#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioFormat>

#include <QDebug>

class AudioDevice : public QIODevice
{
	Q_OBJECT
public:
	AudioDevice(QObject *parent = 0);
	qreal currentFrequency() const;
protected:
	virtual qint64 readData(char *data, qint64 maxlen);
	virtual qint64 writeData(const char *data, qint64 len);
private:
    qreal m_currentFrequency;
};

class FrequencyAnalyzer;
class FrequencyAnalyzerPrivate
{
	Q_DECLARE_PUBLIC(FrequencyAnalyzer)
public:
	FrequencyAnalyzerPrivate(FrequencyAnalyzer *q) : q_ptr(q), input(0), device(0) {}
	~FrequencyAnalyzerPrivate() {}

	FrequencyAnalyzer *q_ptr;
	QAudioInput *input;
	AudioDevice *device;

	void _q_on_notify()
	{
	}
};

#endif // FREQUENCYANALYZER_P_H
