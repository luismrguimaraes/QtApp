pragma Singleton
import QtQuick 6.7

import "keyboardScript.js" as KeyboardScript

QtObject {
    function test(){
        console.log("test")

        KeyboardScript.createKeyboard()
    }
}
