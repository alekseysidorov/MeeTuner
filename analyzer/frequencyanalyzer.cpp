#include "frequencyanalyzer_p.h"

FrequencyAnalyzer::FrequencyAnalyzer(QObject *parent) :
	QObject(parent),
	d_ptr(new FrequencyAnalyzerPrivate(this))
{
	Q_D(FrequencyAnalyzer);

	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();

    qDebug() << "device name: " << info.deviceName() << "\n"
             << "supported frequency:" << info.supportedFrequencies() << "\n"
             << "supported codecs" << info.supportedCodecs() << "\n"
             << "supported sample sizes" << info.supportedSampleSizes();

	QAudioFormat format = info.preferredFormat();
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
    format.setFrequency(info.supportedFrequencies().last());

    if (!info.isFormatSupported(format))
        qWarning("Format is unsupported");

	d->input = new QAudioInput(info, format, this);

	connect(d->input, SIGNAL(notify()), this, SLOT(_q_on_notify()));

	d->device = new AudioDevice(this);
	d->input->start(d->device);
}

FrequencyAnalyzer::~FrequencyAnalyzer()
{

}

qreal FrequencyAnalyzer::currentFrequency() const
{
    return d_func()->device->currentFrequency();
}

void FrequencyAnalyzer::start()
{
	Q_D(FrequencyAnalyzer);
}

AudioDevice::AudioDevice(QObject *parent) : QIODevice(parent)
{
	open(WriteOnly);
}

qreal AudioDevice::currentFrequency() const
{
    return m_currentFrequency;
}

qint64 AudioDevice::readData(char *data, qint64 maxlen)
{
	Q_UNUSED(data);
	Q_UNUSED(maxlen);
	return 0;
}

qint64 AudioDevice::writeData(const char *data, qint64 len)
{
	qDebug() << "Bytes received: " << len;
	return len;
}

#include "moc_frequencyanalyzer.cpp"
