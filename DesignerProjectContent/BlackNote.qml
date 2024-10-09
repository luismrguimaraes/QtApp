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
    property bool noteActive: false
    property int note

    onIsPressedChanged: {
        isPressed ? blackNote.y = blackNote.y -15 : blackNote.y = blackNote.y + 15
    }

    onEnteredTriggerBody: body => {if (body.note === blackNote.note) noteActive = true}
    onExitedTriggerBody:  body => {if (body.note === blackNote.note) noteActive = false}

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
