/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as QQC
import org.kde.kirigami as Kirigami

Kirigami.OverlayDrawer {
    required property FontFeatureModel featureModel
    required property VariableAxisModel axisModel
    property var features
    property var variableAxes

    edge: Qt.BottomEdge
    modal: false

    contentItem: QQC.ScrollView {
        ColumnLayout {
            Kirigami.Heading {
                text: i18n("Variable axes")
                level: 2
            }

            ListView {
                Layout.fillWidth: true
                height: contentHeight

                model: axisModel
                delegate: QQC.CheckDelegate {
                    required property string tag

                    text: tag
                }
            }

            Kirigami.Heading {
                text: i18n("OpenType features")
                level: 2
            }

            ListView {
                Layout.fillWidth: true
                height: contentHeight

                model: featureModel
                delegate: QQC.CheckDelegate {
                    required property string tag

                    Layout.fillWidth: true
                    text: tag
                }
            }
        }
    }
}
