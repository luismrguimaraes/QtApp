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
    property int note

    onIsPressedChanged: {
        isPressed ? whiteNote.y = whiteNote.y -15 : whiteNote.y = whiteNote.y + 15
    }

    Model {
                    id: whiteNoteModel

                    source: "#Cube"
                    materials: isPressed ? defaultMaterial : white
                    Node {
                        id: __materialLibrary__
                    }
                }

}
