#ifndef NOTEANALYZER_P_H
#define NOTEANALYZER_P_H

#include "noteanalyzer.h"
#include "frequencyanalyzer.h"

class NoteAnalyzer;
class NoteAnalyzerPrivate
{
    Q_DECLARE_PUBLIC(NoteAnalyzer)
public:
    NoteAnalyzerPrivate(NoteAnalyzer *q) : q_ptr(q), analyzer(new FrequencyAnalyzer(q)) {}
    NoteAnalyzer *q_ptr;

    FrequencyAnalyzer *analyzer;

    Note nearestNote;
    Octave currentOctave;
    qreal deviation;
};


#endif // NOTEANALYZER_P_H
