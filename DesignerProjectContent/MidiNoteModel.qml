import QtQuick 2.15
import QtQuick3D 6.7
//import MyModule

Model {
    id: midiNoteModel

    x: 0
    y: 0
    z: 0
    source: "#Cube"
    Timer {
        interval: 10; running: true; repeat: true
        onTriggered: midiNoteModel.z--
    }
    //instancing: MyInstancing{}
    Node {
        id: __materialLibrary__
    }
}
/*##^##
Designer {
    D{i:0;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/
