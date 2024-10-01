import QtQuick 2.15
import QtQuick3D 6.7
import MyInstancingModule

Model {
    id: cubeModel

    x: 0
    y: 0
    z: 0
    source: "#Cube"
    instancing: MyInstancing{}
        PropertyAnimation {
            id: propertyAnimation
            target: cubeModel
            property: "x"
            loops: -1
            running: true;
            from: cubeModel.x
            to: cubeModel.x + 100
            duration: 1000
        }

        Node {
            id: __materialLibrary__
        }
    }
/*##^##
Designer {
    D{i:0;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/
