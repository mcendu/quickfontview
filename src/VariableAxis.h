/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_VARIABLEAXIS_H
#define QFV_VARIABLEAXIS_H

#include <QObject>
#include <QtQmlIntegration>
#include <QString>

class VariableAxis : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Use FontScanner to query font features.")
    Q_PROPERTY(QString tag READ tag CONSTANT)
    Q_PROPERTY(qreal minValue READ minValue CONSTANT)
    Q_PROPERTY(qreal maxValue READ maxValue CONSTANT)
    Q_PROPERTY(qreal defaultValue READ defaultValue CONSTANT)
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

    const QString &tag() const
    {
        return m_tag;
    }

    qreal minValue() const
    {
        return m_min;
    }

    qreal maxValue() const
    {
        return m_max;
    }

    qreal defaultValue() const
    {
        return m_default;
    }
};

inline size_t qHash(const VariableAxis &key, size_t seed)
{
    return qHash(key.tag(), seed);
}

#endif
