/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
import QtQuick
import org.kde.kirigami as Kirigami

Kirigami.Page {
    id: page

    property string fontPath: "/usr/share/fonts/google-noto/NotoSans-Italic.ttf"
    property FontFeatureModel featureModel: FontScanner.scanFeatures(fontPath, 0)
    property VariableAxisModel axisModel: FontScanner.scanVariableAxes(fontPath, 0)

    function getFeatures() {
        featureModel = FontScanner.scanFeatures(fontPath, 0);
        axisModel = FontScanner.scanVariableAxes(fontPath, 0);
    }

    FontLoader {
        id: loader
        source: `file:/${page.fontPath}`
        onStatusChanged: function() {
            if (status == FontLoader.Ready) {
                page.getFeatures();
            }
        }
    }

    onFontPathChanged: loader.source = `file:/${fontPath}`

    title: loader.font.family

    FontView {
        id: fontView
        font.family: loader.font.family
    }

    FeaturesDrawer {
        id: featuresDrawer
        featureModel: page.featureModel
        axisModel: page.axisModel

        onAxisChanged: function(axis, value) {
            fontView.font.variableAxes[axis] = value;
        }
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
    