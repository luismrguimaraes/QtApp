import QtQuick 6.7
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule


StaticRigidBody {
    id: whiteNote
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
        isPressed ? whiteNote.y = whiteNote.y -15 : whiteNote.y = whiteNote.y + 15

        if (isPressed){
            if (noteActive) console.log("OKAY")
            else console.log("not okay")
        }
    }

    onEnteredTriggerBody: body => {if (body.note === whiteNote.note)
                              noteActive = true}
    onExitedTriggerBody:  body => {if (body.note === whiteNote.note)
                              noteActive = false}

    Model {
                    id: whiteNoteModel

                    source: "#Cube"
                    materials: isPressed ? defaultMaterial : white
                    Node {
                        id: __materialLibrary__
                    }
                }

}
