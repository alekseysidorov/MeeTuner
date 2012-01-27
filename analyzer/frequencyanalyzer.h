#ifndef FREQUENCYANALYZER_H
#define FREQUENCYANALYZER_H

#include <QObject>

class FrequencyAnalyzerPrivate;
class FrequencyAnalyzer : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(FrequencyAnalyzer)

    Q_PROPERTY(qreal currentFrequency READ currentFrequency NOTIFY currentFrequencyChanged)
public:
	explicit FrequencyAnalyzer(QObject *parent = 0);
	~FrequencyAnalyzer();
	qreal currentFrequency() const;
public slots:
	void start();
	void stop();
    void suspend();
    void resume();
signals:
	void currentFrequencyChanged(qreal frequency);
protected:
	QScopedPointer<FrequencyAnalyzerPrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_onReadyRead())
};

#endif // FREQUENCYANALYZER_H
