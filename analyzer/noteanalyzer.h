#ifndef NOTEANALYZER_H
#define NOTEANALYZER_H

#include <QObject>

typedef QString Note; //TODO
typedef int Octave;

class FrequencyAnalyzer;
class NoteAnalyzerPrivate;
class NoteAnalyzer : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(NoteAnalyzer)

    Q_PROPERTY(Note nearestNote READ nearestNote NOTIFY noteChanged)
    Q_PROPERTY(Note deviation READ deviation NOTIFY deviationChanged)
    Q_PROPERTY(Note octave READ currentOctave NOTIFY octaveChanged)
    Q_PROPERTY(FrequencyAnalyzer* frequencyAnalyzer READ frequencyAnalyzer)
public:
    NoteAnalyzer();
    virtual ~NoteAnalyzer();

    Note nearestNote() const;
    qreal deviation() const;
    Octave currentOctave() const;
    FrequencyAnalyzer *frequencyAnalyzer() const;
signals:
    void noteChanged(Note now);
    void deviationChanged(qreal deviation);
    void octaveChanged(Octave octave);
protected:
    QScopedPointer<NoteAnalyzerPrivate> d_ptr;
};


#endif // NOTEANALYZER_H
