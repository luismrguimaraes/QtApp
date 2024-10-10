import QtQuick 6.7
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule
import "keyboardScript.js" as KS


Node {
    id: noteExtension

    property bool isPressed: audioMidi.pressedNotesList[note]
    property int note

    y: 100


    Model {
            id: noteExtensionModel

            source: "#Rectangle"
            eulerRotation.x: -90
            materials: KS.isBlackMidiNote(note) ? black2 : white2
        }
}
