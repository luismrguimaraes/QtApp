import QtQuick 2.15
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule
import "./keyboardScript.js" as KS


TriggerBody{
    id: midiNoteRigidbody
    collisionShapes: BoxShape {
        id: boxShape
    }
    receiveTriggerReports: true
    sendTriggerReports: true

    Timer {
        interval: 40; running: true; repeat: true
        onTriggered: midiNoteRigidbody.z--
    }

    property int note: -1

    Model {
            id: midiNoteModel

            source: "#Cube"
            materials: KS.isBlackMidiNote(note) ? black : white
            Node {
                id: __materialLibrary__
            }
        }
}


/*##^##
Designer {
    D{i:0;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/
