#ifndef UTILS_H
#define UTILS_H


#include <QtCore/qobject.h>
#include <QSet>

namespace utils {

inline bool isBlackMidiNote(qint32 note) {
    // Black notes in an octave (C#=1, D#=3, F#=6, G#=8, A#=10)
    QSet<int> blackNotes {1, 3, 6, 8, 10};

    // MIDI note numbers repeat every 12 notes (one octave)
    return blackNotes.find(note % 12) != blackNotes.end();
}

inline QString midiNoteToName(int midiNote) {
    // Array of note names
    const QString noteNames[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    // Calculate the note name and octave
    int noteIndex = midiNote % 12;
    int octave = (midiNote / 12) - 1;

    // Construct the result string
    QString noteName = noteNames[noteIndex] + QString::number(octave);

    return noteName;
}

inline int freqToMidi(double freq){
    return (int) ( ( 12 * log(freq / 220.0) / log(2.0) ) + 57.01 );
}
inline double midiToFreq (int n){
    return 440 * std::pow(2, (n - 69.0)/12.0);
}

}
#endif // UTILS_H
