/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

ColumnLayout {
    property font font

    id: view
    Layout.fillWidth: true
    Kirigami.Theme.colorSet: Kirigami.Theme.View

    component FontSizePreviewText: Controls.Label {
        font.family: view.font.family
        font.weight: view.font.weight
        font.italic: view.font.italic
        font.features: view.font.features
        font.variableAxes: view.font.variableAxes

        text: i18nc("Example text",
            "The quick brown fox jumps over the lazy dog. 0123456789")
    }

    Kirigami.Heading {
        font.family: view.font.family
        font.weight: view.font.weight
        font.italic: view.font.italic
        font.features: view.font.features
        font.variableAxes: view.font.variableAxes

        text: i18nc("%1 font family", "%1", view.font.family)
        level: 1
    }

    Controls.Label {
        font.family: view.font.family
        font.weight: view.font.weight
        font.italic: view.font.italic
        font.features: view.font.features
        font.variableAxes: view.font.variableAxes

        text: i18nc("The basic set of characters", "\
            ABCDEFGHIJKLMNOPQRSTUVWXYZ<br />\
            abcdefghijklmnopqrstuvwxyz<br />\
            0123456789 .,'\":;!?/\+-_|=~[]{}()<>@#$%^&*`\
        ")
    }

    FontSizePreviewText { font.pointSize: 10 }
    FontSizePreviewText { font.pointSize: 12 }
    FontSizePreviewText { font.pointSize: 14 }
    FontSizePreviewText { font.pointSize: 16 }
    FontSizePreviewText { font.pointSize: 20 }
    FontSizePreviewText { font.pointSize: 24 }
    FontSizePreviewText { font.pointSize: 28 }
    FontSizePreviewText { font.pointSize: 32 }
    FontSizePreviewText { font.pointSize: 40 }
    FontSizePreviewText { font.pointSize: 48 }
    FontSizePreviewText { font.pointSize: 56 }
    FontSizePreviewText { font.pointSize: 64 }
    FontSizePreviewText { font.pointSize: 72 }
}
