var blacknote
var whitenote
var noteExt
const objects = []
const noteExtObjects = []


function isBlackMidiNote(note) {
    // Black notes in an octave (C#=1, D#=3, F#=6, G#=8, A#=10)
    const blackNotes = new Set([1, 3, 6, 8, 10]);

    // MIDI note numbers repeat every 12 notes (one octave)
    return blackNotes.has(note % 12);
}

function createKeyboard() {
    blacknote = Qt.createComponent("BlackNote.qml");
    whitenote = Qt.createComponent("WhiteNote.qml");
    noteExt = Qt.createComponent("KeyExtension.qml");

    for (var note = 0 ; note <= 127; note++){
        var xPos = note - 60;

        var zScale = 0.5;
        var zPos = -25;
        var yPos = 100;
        var xScale = 0.25;

        if (!isBlackMidiNote(note)){
            zScale = 1;
            zPos = -50;
            yPos = 80;
            xScale = 0.4;
        }

        var xPosFinal = -xPos*25
        var zPosFinal = zPos -500

        var newObject
        var newNoteExt
        if (isBlackMidiNote(note)){
            newObject = blacknote.createObject(sceneKeyboard,
                                               {x:xPosFinal, y: yPos, z:zPosFinal, scale: Qt.vector3d(xScale,1,zScale), note: note});
            newNoteExt = noteExt.createObject(sceneKeyboard,
                                              {x:xPosFinal, scale: Qt.vector3d(xScale*0.6,1,100), note: note});

        }
        else{
            newObject = whitenote.createObject(sceneKeyboard,
                                               {x:xPosFinal, y: yPos, z:zPosFinal, scale: Qt.vector3d(xScale,1,zScale), note: note});
            newNoteExt = noteExt.createObject(sceneKeyboard,
                                              {x:xPosFinal, scale: Qt.vector3d(xScale*0.6,1,100), note: note});

        }

        if (newObject === null) {
            // Error Handling
            console.log("Error creating object");
            return
        }

        objects.push(newObject);
        noteExtObjects.push(newNoteExt)
    }
}
