#include "frequencyanalyzer_p.h"
#include <QThread>

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
             << "supported sample types" << info.supportedSampleTypes() << "\n";

    QAudioFormat format = info.preferredFormat();
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setSampleSize(32);
    format.setFrequency(d->sampling = info.supportedFrequencies().last());

    if (!info.isFormatSupported(format)) {
        qWarning("Format is unsupported");
        return;
    }

    d->input = new QAudioInput(info, format, this);
    connect(d->input, SIGNAL(stateChanged(QAudio::State)), SLOT(_q_stateChanged(QAudio::State)));
}

FrequencyAnalyzer::~FrequencyAnalyzer()
{
    stop();
}

qreal FrequencyAnalyzer::currentFrequency() const
{
    return d_func()->frequency;
}

FrequencyAnalyzer::State FrequencyAnalyzer::state() const
{
    return static_cast<State>(d_func()->input->state());
}

void FrequencyAnalyzer::start()
{
    Q_D(FrequencyAnalyzer);
    if (d->device) {
        //TODO
        d->device->deleteLater();
    }
    d->device = d->input->start();
    connect(d->device, SIGNAL(readyRead()), SLOT(_q_onReadyRead()));
}

void FrequencyAnalyzer::stop()
{
    Q_D(FrequencyAnalyzer);
    if (d->input->state() == QAudio::ActiveState)
        d->input->stop();
}

void FrequencyAnalyzer::suspend()
{
    Q_D(FrequencyAnalyzer);
    if (d->input->state() == QAudio::ActiveState)
        d->input->suspend();
}

void FrequencyAnalyzer::resume()
{
    Q_D(FrequencyAnalyzer);
    if (d->input->state() == QAudio::IdleState)
        d->input->resume();
}

#include "moc_frequencyanalyzer.cpp"
