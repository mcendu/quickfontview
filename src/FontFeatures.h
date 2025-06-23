/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_FONTFEATURES_H
#define QFV_FONTFEATURES_H

#include <QByteArray>
#include <QHash>
#include <QList>
#include <QObject>
#include <QSet>
#include <QString>
#include <qcontainerfwd.h>
#include <utility>

class VariableAxis : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tag MEMBER m_tag READ tag)
    Q_PROPERTY(qreal min MEMBER m_min READ minValue)
    Q_PROPERTY(qreal max MEMBER m_max READ maxValue)
    Q_PROPERTY(qreal default MEMBER m_default READ defaultValue)
private:
    QString m_tag;
    qreal m_min;
    qreal m_max;
    qreal m_default;

public:
    VariableAxis(QString tag, qreal minValue, qreal maxValue, qreal defaultValue)
        : m_tag(tag)
        , m_min(minValue)
        , m_max(maxValue)
        , m_default(defaultValue) { };

    const QString &tag() const {
        return m_tag;
    }

    qreal minValue() const {
        return m_min;
    }

    qreal maxValue() const {
        return m_max;
    }

    qreal defaultValue() const {
        return m_default;
    }
};

size_t qHash(const VariableAxis &key, size_t seed);

class FontFeatures : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSet<QString> features MEMBER m_features READ features)
    Q_PROPERTY(QHash<QString, VariableAxis *> variableAxes MEMBER m_axes READ axes)
private:
    QSet<QString> m_features;
    QHash<QString, VariableAxis *> m_axes;

public:
    FontFeatures(QSet<QString> &&features, QHash<QString, VariableAxis *> &&axes)
        : m_features(std::move(features))
        , m_axes(std::move(axes))
    {
    }

    const QSet<QString> &features() const {
        return m_features;
    }

    const QHash<QString, VariableAxis *> &axes() const {
        return m_axes;
    }
};

#endif
