#include "noteanalyzer_p.h"
#include <QThread>

#include <QTimer>

NoteAnalyzer::NoteAnalyzer() :
    d_ptr(new NoteAnalyzerPrivate(this))
{
    Q_D(NoteAnalyzer);
    d->analyzer = new FrequencyAnalyzer;
    connect(d->analyzer, SIGNAL(currentFrequencyChanged(qreal)), SLOT(_q_onFrequencyChanged(qreal)));
    getNote_initialize(); //TODO and what will happen in case of re-calling this method?

    //d->thread = new QThread;
    //d->analyzer->moveToThread(d->thread);
    //d->thread->start(QThread::LowPriority);
    //connect(d->thread, SIGNAL(finished()), SLOT(deleteLater()));
}

NoteAnalyzer::~NoteAnalyzer()
{
    Q_D(NoteAnalyzer);
    //d->thread->quit();
    d->analyzer->deleteLater();
}

QString NoteAnalyzer::nearestNote() const
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

#include "moc_noteanalyzer.cpp"
