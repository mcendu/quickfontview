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
    signal featureChanged(string feature, bool enabled)

    edge: Qt.BottomEdge
    modal: false

    component VariableAxisDelegate: ColumnLayout {
        id: delegate
        required property real value
        required property real minValue
        required property real maxValue
        required property real defaultValue
        required property string tag
        required property string description

        required property var model

        width: ListView.view.width
        spacing: 0

        QQC.Label {
            text: delegate.description
        }

        QQC.Slider {
            id: slider
            Layout.fillWidth: true

            from: delegate.minValue
            to: delegate.maxValue
            value: delegate.defaultValue
            stepSize: 1
            snapMode: QQC.Slider.NoSnap
            onValueChanged: delegate.model.value = value
        }
    }

    contentItem: QQC.ScrollView {
        contentWidth: availableWidth

        ColumnLayout {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            Kirigami.Heading {
                Layout.topMargin: 10
                Layout.bottomMargin: 4
                text: i18n("Variable axes")
                level: 2

                visible: axes.count != 0
                enabled: axes.count != 0
            }

            ListView {
                id: axes
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.bottomMargin: 8
                spacing: 8

                visible: count != 0
                enabled: count != 0

                model: drawer.axisModel
                delegate: VariableAxisDelegate {
                    onValueChanged: drawer.axisChanged(tag, value)
                }
                reuseItems: true
            }

            Kirigami.Heading {
                text: i18n("OpenType features")
                level: 2

                visible: features.count != 0
                enabled: features.count != 0
            }

            ListView {
                id: features
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight

                visible: count != 0
                enabled: count != 0

                model: drawer.featureModel
                delegate: QQC.CheckDelegate {
                    required property string tag
                    required property string description
                    required property bool enabled
                    required property var model

                    width: ListView.view.width
                    text: description

                    onCheckStateChanged: {
                        model.enabled = checkState == Qt.Checked;
                    }

                    onEnabledChanged: drawer.featureChanged(tag, enabled)
                }
            }
        }
    }
}
