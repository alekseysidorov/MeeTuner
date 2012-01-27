#ifndef FREQUENCYANALYZER_H
#define FREQUENCYANALYZER_H

#include <QObject>

class FrequencyAnalyzerPrivate;
class FrequencyAnalyzer : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(FrequencyAnalyzer)
public:
	explicit FrequencyAnalyzer(QObject *parent = 0);
	~FrequencyAnalyzer();
	qreal currentFrequency() const;

	void start();
	void stop();
signals:
	void currentFrequencyChanged(qreal frequency);
protected:
	QScopedPointer<FrequencyAnalyzerPrivate> d_ptr;

	Q_PRIVATE_SLOT(d_func(), void _q_on_notify())
};

#endif // FREQUENCYANALYZER_H
