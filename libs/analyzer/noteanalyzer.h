#ifndef NOTEANALYZER_H
#define NOTEANALYZER_H

#include <QObject>

class FrequencyAnalyzer;
class NoteAnalyzerPrivate;
class NoteAnalyzer : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(NoteAnalyzer)

    Q_PROPERTY(QString nearestNote READ nearestNote NOTIFY noteChanged)
    Q_PROPERTY(qreal deviation READ deviation NOTIFY deviationChanged)
    Q_PROPERTY(int octave READ currentOctave NOTIFY octaveChanged)
    Q_PROPERTY(FrequencyAnalyzer* frequencyAnalyzer READ frequencyAnalyzer)
public:
    NoteAnalyzer();
    virtual ~NoteAnalyzer();

    QString nearestNote() const;
    qreal deviation() const;
    int currentOctave() const;
    FrequencyAnalyzer *frequencyAnalyzer() const;
signals:
    void noteChanged(const QString &now);
    void deviationChanged(qreal deviation);
    void octaveChanged(int octave);
protected:
    QScopedPointer<NoteAnalyzerPrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_onFrequencyChanged(qreal))
};


#endif // NOTEANALYZER_H
