import QtQuick 6.7
import MyModule

Node {
    id: game

    property real score: 0
    property real interval: 30

    Timer {
        id: clock
        interval: game.interval
        running: false
        repeat: true
        onTriggered: {
            sceneMidiNotesInstancer.moveNotes();

            for (var key of sceneKeyboard.getKeyObjects()){
                if (key.isPressed){
                    if (key.collisionCount > 0)
                        score += 0.1
                    else score -= 0.05
                }
                else{
                    if (key.collisionCount > 0)
                        score -= 0.05
                }
            }
        }
    }

    function startStop() {
        clock.running = clock.running ? false : true;
    }

    function readFile(path){
        sceneMidiNotesInstancer.readFile(path)
    }

    MidiNotesInstancer {
        id: sceneMidiNotesInstancer
        x: 0
        y: 100
        visible: true
        z: 0
    }

    Keyboard{
        id: sceneKeyboard
    }
}

