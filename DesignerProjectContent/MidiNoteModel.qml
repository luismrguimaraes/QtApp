import QtQuick 2.15
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule


TriggerBody{
    id: midiNoteRigidbody
    collisionShapes: BoxShape {
        id: boxShape
    }
    receiveTriggerReports: true
    sendTriggerReports: true

    onBodyEntered: {
        console.log("entered")
    }
    onBodyExited: {
        console.log("exited")
    }

    Timer {
        interval: 10; running: true; repeat: true
        onTriggered: midiNoteRigidbody.z--
    }

    Model {
            id: midiNoteModel

            source: "#Cube"

            materials: defaultMaterial
            //instancing: MyInstancing{}

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
