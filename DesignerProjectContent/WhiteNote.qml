import QtQuick 6.7
import QtQuick3D 6.7
import MyModule

Model {
                    id: whiteNote
                    source: "#Cube"
                    materials: white
                    instancing: KeyboardInstancing{
                        isWhiteNote: true
                        pressedNotesList: audioMidi.pressedNotesList
                    }
                    Node {
                        id: __materialLibrary__
                    }
                }
