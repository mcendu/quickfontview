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
#include <QQmlListProperty>
#include <QSet>
#include <QString>
#include <QtQmlIntegration>
#include <qqmlintegration.h>
#include <qqmllist.h>
#include <utility>

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

class FontFeatures : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSet<QString> features READ features CONSTANT)
    Q_PROPERTY(QHash<QString, VariableAxis *> axes READ axes CONSTANT)
private:
    QSet<QString> m_features;
    QHash<QString, VariableAxis *> m_axes;

public:
    FontFeatures(QSet<QString> &&features, QHash<QString, VariableAxis *> &&axes)
        : m_features(std::move(features))
        , m_axes(std::move(axes))
    {
    }

    const QSet<QString> &features() const
    {
        return m_features;
    }

    const QHash<QString, VariableAxis *> &axes() const
    {
        return m_axes;
    }
};

class QmlFontFeatures : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(FontFeatures)
    QML_UNCREATABLE("Use FontScanner to query font features.")
    Q_PROPERTY(QQmlListProperty<const QString> features READ features CONSTANT)
    Q_PROPERTY(QQmlListProperty<const VariableAxis> variableAxes READ axes CONSTANT)
private:
    QList<QString> m_features;
    QList<VariableAxis *> m_axes;

    static qsizetype featureCount(QQmlListProperty<const QString> *);
    static qsizetype axisCount(QQmlListProperty<const VariableAxis> *);
    static const QString *featureAt(QQmlListProperty<const QString> *, qsizetype i);
    static const VariableAxis *axisAt(QQmlListProperty<const VariableAxis> *, qsizetype i);

public:
    QmlFontFeatures(const FontFeatures &cxxfeatures)
        : m_features(cxxfeatures.features().values())
        , m_axes(cxxfeatures.axes().values())
    {
    }

    QQmlListProperty<const QString> features()
    {
        return QQmlListProperty<const QString>(this, nullptr, &featureCount, &featureAt);
    }

    QQmlListProperty<const VariableAxis> axes()
    {
        return QQmlListProperty<const VariableAxis>(this, nullptr, &axisCount, &axisAt);
    }
};

#endif
