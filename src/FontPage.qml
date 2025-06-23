/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.Page {
    id: page

    property string fontPath: "/usr/share/fonts/google-noto/NotoSans-Italic.ttf"
    property FontFeatureModel featureModel: FontScanner.scanFeatures(fontPath, 0)
    property VariableAxisModel axisModel: FontScanner.scanVariableAxes(fontPath, 0)

    function getFeatures() {
        featureModel = FontScanner.scanFeatures(fontPath, 0);
        axisModel = FontScanner.scanVariableAxes(fontPath, 0);

        console.log(`feature count: ${featureModel.rowCount()}`)
    }

    Component.onCompleted: getFeatures();

    FontLoader {
        id: loader
        source: `file:/${fontPath}`
        onStatusChanged: getFeatures();
    }

    onFontPathChanged: loader.source = `file:/${fontPath}`

    title: loader.font.family

    FontView {
        font: loader.font
    }

    FeaturesDrawer {
        id: featuresDrawer
        featureModel: page.featureModel
        axisModel: page.axisModel
        features: loader.font.features
        variableAxes: loader.font.variableAxes
    }

    actions: [
        Kirigami.Action {
            id: previewOptionsAction
            icon.name: "adjustlevels-symbolic"
            text: i18n("Font features")
            onTriggered: function() {
                if (featuresDrawer.visible) {
                    featuresDrawer.close();
                } else {
                    featuresDrawer.open();
                }
            }
        }
    ]
}
    