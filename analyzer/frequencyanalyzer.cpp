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
             << "supported sample sizes" << info.supportedSampleSizes() << "\n"
             << "supported sample types" << info.supportedSampleTypes();

    QAudioFormat format = info.preferredFormat();
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    format.setFrequency(d->sampling = info.supportedFrequencies().last());

    if (!info.isFormatSupported(format))
        qWarning("Format is unsupported");

    d->input = new QAudioInput(info, format, this);

    connect(d->input, SIGNAL(notify()), this, SLOT(_q_on_notify()));
}

FrequencyAnalyzer::~FrequencyAnalyzer()
{

}

qreal FrequencyAnalyzer::currentFrequency() const
{
    return d_func()->frequency;
}

void FrequencyAnalyzer::start()
{
    Q_D(FrequencyAnalyzer);
    //if (!d->device) {
    //    d->device = new AudioDevice(this);
    //}
    if (d->device) {
        //TODO
    }
    d->device = d->input->start();
    connect(d->device, SIGNAL(readyRead()), SLOT(_q_onReadyRead()));
}

void FrequencyAnalyzer::stop()
{
    d_func()->input->stop();
}

void FrequencyAnalyzer::suspend()
{
    d_func()->input->suspend();
}

void FrequencyAnalyzer::resume()
{
    d_func()->input->resume();
}

#include "moc_frequencyanalyzer.cpp"
