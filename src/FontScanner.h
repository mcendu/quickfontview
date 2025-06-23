/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_FONTSCANNER_H
#define QFV_FONTSCANNER_H

#include "FontFeature.h"
#include "VariableAxis.h"
#include <QString>
#include <QVariant>
#include <harfbuzz/hb.h>
#include <qtmetamacros.h>

class FontScanner : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    Q_INVOKABLE static const FontFeatureModel *scanFeatures(const QString &path, size_t index);
    Q_INVOKABLE static const VariableAxisModel *scanVariableAxes(const QString &path, size_t index);

    static QSet<QString> scanFeaturesRaw(hb_face_t *face);
    static QHash<QString, VariableAxis *> scanVariableAxesRaw(hb_face_t *face);
};

#endif
