import QtQuick 2.15
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule
import "midiNotesScript.js" as MidiNotesScript

Node{
    id: midiNotesInstancer

    function readFile(path){
        audioMidi.readMidiData(path)
        MidiNotesScript.createMidiNotes()
    }

    function moveNotes(){
        MidiNotesScript.moveNotes()
    }

    Component.onCompleted: readFile(":/midi/test.mid")
}
