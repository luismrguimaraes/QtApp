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

    onEnteredTriggerBody: {
        console.log(note)
    }

    property bool isPressed: false
    property int note: -1

    Model {
                    id: blackNote

                    source: "#Cube"
                    materials: black
                    //instancing: KeyboardInstancing{
                    //    isWhiteNote: false
                    //    pressedNotesList: audioMidi.pressedNotesList
                    //}
                    Node {
                        id: __materialLibrary__
                    }
                }

}
