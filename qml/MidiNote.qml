import QtQuick 2.15
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule
import "./keyboardScript.js" as KS


StaticRigidBody {
    id: midiNote
    collisionShapes: BoxShape {
        id: boxShape
    }
    receiveTriggerReports: true
    sendTriggerReports: true

    property bool isPressed: audioMidi.pressedNotesList[note]
    property bool colliding : false
    property int note: -1

    onEnteredTriggerBody: body => {
                          if (body.note === note)
                              colliding = true
                          }
    onExitedTriggerBody: destroy(20)

    Model {
            id: midiNoteModel

            source: "#Cube"
            materials: colliding ?
                           isPressed ?
                               defaultMaterial : red
                        : KS.isBlackMidiNote(note) ?
                               black : white
        }
}


/*##^##
Designer {
    D{i:0;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/
