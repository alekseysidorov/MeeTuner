#include "noteanalyzer_p.h"

NoteAnalyzer::NoteAnalyzer() :
    d_ptr(new NoteAnalyzerPrivate(this))
{

}

NoteAnalyzer::~NoteAnalyzer()
{

}

Note NoteAnalyzer::nearestNote() const
{
    return d_func()->nearestNote;
}

qreal NoteAnalyzer::deviation() const
{
    return d_func()->deviation;
}

Octave NoteAnalyzer::currentOctave() const
{
    return d_func()->currentOctave;
}

FrequencyAnalyzer *NoteAnalyzer::frequencyAnalyzer() const
{
    return d_func()->analyzer;
}
