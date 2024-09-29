// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.7

ListModel {
    id: eventListModel

    ListElement {
        eventId: "enterPressed0"
        eventDescription: "Emitted when pressing the enter button"
        shortcut: "Return"
        parameters: "Enter"
    }

    ListElement {
    shortcut: "1"
    eventDescription: ""
    eventId: "1"
    }
}
