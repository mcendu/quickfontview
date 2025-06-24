/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC
import org.kde.kirigami as Kirigami

Kirigami.OverlayDrawer {
    id: drawer
    required property FontFeatureModel featureModel
    required property VariableAxisModel axisModel

    signal axisChanged(string axis, real value)

    edge: Qt.BottomEdge
    modal: false

    component VariableAxisDelegate: ColumnLayout {
        id: delegate
        required property real value
        required property real minValue
        required property real maxValue
        required property real defaultValue
        required property string tag

        required property var model

        width: ListView.view.width

        QQC.Label {
            text: delegate.tag
        }

        QQC.Slider {
            id: slider
            Layout.fillWidth: true

            from: delegate.minValue
            to: delegate.maxValue
            value: delegate.defaultValue
            onValueChanged: delegate.model.value = value
        }
    }

    contentItem: QQC.ScrollView {
        ColumnLayout {
            anchors.fill: parent

            Kirigami.Heading {
                text: i18n("Variable axes")
                level: 2
            }

            ListView {
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight

                model: drawer.axisModel
                delegate: VariableAxisDelegate {
                    onValueChanged: drawer.axisChanged(tag, value)
                }
                reuseItems: true
            }

            Kirigami.Heading {
                text: i18n("OpenType features")
                level: 2
            }

            ListView {
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight

                model: drawer.featureModel
                delegate: QQC.CheckDelegate {
                    required property string tag

                    width: ListView.view.width
                    text: tag
                }
            }
        }
    }
}
