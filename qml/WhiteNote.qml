import QtQuick 6.7
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule
import QtQuick3D.Particles3D

TriggerBody{
    id: whiteNote
    collisionShapes: BoxShape {
        id : boxShape

        extents: Qt.vector3d(10,100,10)
        z: 50
    }
    receiveTriggerReports: true
    sendTriggerReports: true

    property bool isPressed: audioMidi.pressedNotesList[note]
    property int collisionCount: 0
    property int note

    onIsPressedChanged: {
        isPressed ? whiteNote.y = whiteNote.y -20 : whiteNote.y = whiteNote.y + 20
    }

    onBodyEntered: body => {if (body.note === note)
                        collisionCount++}
    onBodyExited: body => {if (body.note === note)
                        collisionCount--}

    Model {
                    id: whiteNoteModel

                    source: "#Cube"
                    materials: isPressed && collisionCount > 0 ? defaultMaterial : white
                }
}
