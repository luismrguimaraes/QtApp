import QtQuick 6.7
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule

StaticRigidBody {
    id: blackNote
    collisionShapes: BoxShape {
        id : boxShape

        z: 100
        scale.z: 0.5
    }
    receiveTriggerReports: true
    sendTriggerReports: true

    property bool isPressed: audioMidi.pressedNotesList[note]
    property int note

    onIsPressedChanged: {
        isPressed ? blackNote.y = blackNote.y -15 : blackNote.y = blackNote.y + 15
    }

    Model {
                    id: blackNoteModel

                    source: "#Cube"
                    materials: isPressed ? defaultMaterial : black

                    //instancing: KeyboardInstancing{
                    //    isWhiteNote: false
                    //    pressedNotesList: audioMidi.pressedNotesList
                    //}
                    Node {
                        id: __materialLibrary__
                    }
                }

}
