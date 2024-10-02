// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.7
import QtQuick.Controls 6.7
import DesignerProject
import MyModule

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "DesignerProject"

    Screen01 {
        id: mainScreen
    }

    Button {
        id: button
        text: qsTr("440Hz")
        onClicked: myObject.handleButtonClick(440)
    }
    Button {
        id: button2
        text: qsTr("880Hz")
        anchors.left: button.right
        onClicked: myObject.handleButtonClick(880)
    }
}

