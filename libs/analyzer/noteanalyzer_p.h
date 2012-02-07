#ifndef NOTEANALYZER_P_H
#define NOTEANALYZER_P_H

#include "noteanalyzer.h"
#include "frequencyanalyzer.h"
#include <getNote.h>

#include <QDebug>

class QThread;
class NoteAnalyzer;
class NoteAnalyzerPrivate
{
    Q_DECLARE_PUBLIC(NoteAnalyzer)
public:
    NoteAnalyzerPrivate(NoteAnalyzer *q) : q_ptr(q), analyzer(0), thread(0),
        currentOctave(0), deviation(0) {}
    NoteAnalyzer *q_ptr;

    FrequencyAnalyzer *analyzer;
    QThread *thread;

    QString nearestNote;
    int currentOctave;
    qreal deviation;

    void setNote(const QString &name)
    {
        Q_Q(NoteAnalyzer);
        if (nearestNote == name)
            return;
        nearestNote = name;
        emit q->noteChanged(nearestNote);
    }

    void setDeviation(qreal deviation)
    {
        Q_Q(NoteAnalyzer);
        if (qFuzzyCompare(this->deviation, deviation))
            return;
        this->deviation = deviation;
        emit q->deviationChanged(deviation);
    }

    void setOctave(int octave)
    {
        Q_Q(NoteAnalyzer);
        if (currentOctave == octave)
            return;
        currentOctave = octave;
        emit q->octaveChanged(octave);
    }

    void _q_onFrequencyChanged(qreal frequency)
    {
        if (frequency < 20) {
            setDeviation(0);
            setNote(QString());
            setOctave(0);
            return;
        }

        real32_T f = frequency;
        real32_T noteFreq = 0;
        real32_T noteError = 0;
        int32_T noteOctave = 0;
        QByteArray name = "NaN";

        getNote(f, &noteFreq, &noteError, name.data(), &noteOctave);
        setDeviation(noteError);
        setNote(name.trimmed());
        setOctave(noteOctave);
    }
};


#endif // NOTEANALYZER_P_H
