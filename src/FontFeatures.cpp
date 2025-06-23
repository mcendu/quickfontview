/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "FontFeatures.h"

qsizetype QmlFontFeatures::featureCount(QQmlListProperty<const QString> *list)
{
    auto features = qobject_cast<QmlFontFeatures *>(list->object);
    return features->m_features.count();
}

const QString *QmlFontFeatures::featureAt(QQmlListProperty<const QString> *list, qsizetype i)
{
    auto features = qobject_cast<QmlFontFeatures *>(list->object);
    return &features->m_features.at(i);
}

qsizetype QmlFontFeatures::axisCount(QQmlListProperty<const VariableAxis> *list)
{
    auto features = qobject_cast<QmlFontFeatures *>(list->object);
    return features->m_axes.count();
}

const VariableAxis *QmlFontFeatures::axisAt(QQmlListProperty<const VariableAxis> *list, qsizetype i)
{
    auto features = qobject_cast<QmlFontFeatures *>(list->object);
    return features->m_axes.at(i);
}
