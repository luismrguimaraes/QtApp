// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.7
import QtQuick.Controls 6.7
import DesignerProject

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "DesignerProject"

    Screen01 {
        id: mainScreen
    }
}

