/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
import QtQuick
import org.kde.kirigami as Kirigami

Kirigami.Page {
    id: page

    property string file
    property FontFeatureModel featureModel: FontScanner.scanFeatures(file, 0)
    property VariableAxisModel axisModel: FontScanner.scanVariableAxes(file, 0)

    function getFeatures() {
        featureModel = FontScanner.scanFeatures(file, 0);
        axisModel = FontScanner.scanVariableAxes(file, 0);
    }

    FontLoader {
        id: loader
        source: `file://${page.file}`
        onStatusChanged: function() {
            if (status == FontLoader.Ready) {
                page.getFeatures();
            }
        }
    }

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
            if (axis !== "") {
                fontView.font.variableAxes[axis] = value;
            }
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
    