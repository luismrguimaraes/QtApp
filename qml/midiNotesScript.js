var midiNote
const noteObjects = []

function createMidiNotes() {
    // clear noteObjects
    console.log(noteObjects.length + " objects to destroy")
    for (var j in noteObjects) {
        noteObjects[j].destroy();
    }
    noteObjects.length = 0;

    var notesInfo = audioMidi.midiNotesInfo;
    midiNote = Qt.createComponent("MidiNote.qml");

    var i = 0
    while (i < notesInfo.length){
        var newObject = midiNote.createObject(midiNotesInstancer,
            {x:notesInfo[i+1], y: notesInfo[i+2], z:notesInfo[i+3],
            scale: Qt.vector3d(notesInfo[i+4],notesInfo[i+5],notesInfo[i+6]),
            note: notesInfo[i]});

        if (newObject === null) {
            // Error Handling
            console.log("Error creating midi objects");
            return
        }

        noteObjects.push(newObject)

        i += 7
    }
}
