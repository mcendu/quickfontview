/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.Page {
    property string fontPath: "/usr/share/fonts/google-noto/NotoSans-Italic.ttf"

    FontLoader {
        id: loader
        source: `file:/${fontPath}`
    }

    title: loader.font.family

    actions: [
        Kirigami.Action {
            id: previewOptionsAction
            icon.name: "adjustlevels-symbolic"
            text: i18n("Font features")
        }
    ]

    FontView {
        font: loader.font
    }
}
    