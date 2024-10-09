import QtQuick 6.7
import QtQuick3D 6.7
import MyModule
import "keyboardScript.js" as KeyboardScript

Node {
    id: keyboard

    Component.onCompleted: KeyboardScript.createKeyboard()
}
