import QtQuick 6.7
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule

StaticRigidBody {
    collisionShapes: BoxShape {
        id : boxShape

        z: 100
        scale.z: 0.5
    }
    receiveTriggerReports: true
    sendTriggerReports: true

    property bool isPressed: false
    property int note: -1

    Model {
                    id: whiteNote

                    source: "#Cube"
                    materials: white
                    Node {
                        id: __materialLibrary__
                    }
                }

}
