/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.OverlayDrawer {
    property var features
    property var variableAxes

    edge: Qt.BottomEdge
    modal: false

    contentItem: ColumnLayout {
        Kirigami.Heading {
            text: i18n("Variable axes")
            level: 2
        }

        Kirigami.Heading {
            text: i18n("OpenType features")
            level: 2
        }
    }
}
