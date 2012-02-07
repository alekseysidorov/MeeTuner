#ifndef FREQUENCYANALYZER_H
#define FREQUENCYANALYZER_H

#include <QObject>

class FrequencyAnalyzerPrivate;
class FrequencyAnalyzer : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(FrequencyAnalyzer)

    Q_PROPERTY(qreal currentFrequency READ currentFrequency NOTIFY currentFrequencyChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(qreal threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged)
    Q_ENUMS(State)
public:
    enum State { ActiveState, SuspendedState, StoppedState, IdleState };

	explicit FrequencyAnalyzer(QObject *parent = 0);
	~FrequencyAnalyzer();
	qreal currentFrequency() const;
    qreal threshold() const;
    void setThreshold(qreal value);
    State state() const;
public slots:
	void start();
	void stop();
    void suspend();
    void resume();
signals:
	void currentFrequencyChanged(qreal frequency);
    void stateChanged(FrequencyAnalyzer::State state);
    void thresholdChanged(qreal threshold);
protected:
	QScopedPointer<FrequencyAnalyzerPrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_onReadyRead())
    Q_PRIVATE_SLOT(d_func(), void _q_onStateChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onDeviceDestroyed(QObject*))
};

#endif // FREQUENCYANALYZER_H
