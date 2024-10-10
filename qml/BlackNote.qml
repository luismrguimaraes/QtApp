import QtQuick 6.7
import QtQuick3D 6.7
import QtQuick3D.Physics
import MyModule


TriggerBody {
    id: blackNote
    collisionShapes: BoxShape {
        id : boxShape

        extents: Qt.vector3d(20,100,10)
        z: 50
    }
    receiveTriggerReports: true
    sendTriggerReports: true

    property bool isPressed: audioMidi.pressedNotesList[note]
    property int collisionCount: 0
    property int note

    onIsPressedChanged: {
        isPressed ? blackNote.y = blackNote.y -20 : blackNote.y = blackNote.y + 20
    }

    onBodyEntered: body => {if (body.note === note)
                        collisionCount++}
    onBodyExited: body => {if (body.note === note)
                        collisionCount--}

    Model {
                    id: blackNoteModel

                    source: "#Cube"
                    materials: isPressed && collisionCount > 0 ? defaultMaterial : black
                    Node {
                        id: __materialLibrary__
                    }
                }
}
