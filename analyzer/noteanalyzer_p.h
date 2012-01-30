#ifndef NOTEANALYZER_P_H
#define NOTEANALYZER_P_H

#include "noteanalyzer.h"
#include "frequencyanalyzer.h"
#include "getNote.h"

#include <QDebug>

class QThread;
class NoteAnalyzer;
class NoteAnalyzerPrivate
{
    Q_DECLARE_PUBLIC(NoteAnalyzer)
public:
    NoteAnalyzerPrivate(NoteAnalyzer *q) : q_ptr(q), analyzer(0), thread(0) {}
    NoteAnalyzer *q_ptr;

    FrequencyAnalyzer *analyzer;
    QThread *thread;

    QString nearestNote;
    Octave currentOctave;
    qreal deviation;

    void _q_onFrequencyChanged(qreal frequency)
    {
        Q_Q(NoteAnalyzer);
        real32_T f = frequency;
        real_T noteFreq = 0;
        real32_T noteError = 0;
        real_T noteOctave = 0;
        QByteArray name = "XX";

        getNote(f, &noteFreq, &noteError, name.data(), &noteOctave);

        if (!qFuzzyCompare(noteError, deviation)) {
            deviation = noteError;
            emit q->deviationChanged(deviation);
        }
        if (name != nearestNote) {
            nearestNote = name;
            emit q->noteChanged(nearestNote);
        }
        qDebug() << name << noteError;
    }
};


#endif // NOTEANALYZER_P_H
