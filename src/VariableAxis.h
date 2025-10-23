/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_VARIABLEAXIS_H
#define QFV_VARIABLEAXIS_H

#include <QAbstractListModel>
#include <QObject>
#include <QString>
#include <QtQmlIntegration>
#include <qabstractitemmodel.h>
#include <qvariant.h>

class VariableAxis : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Use FontScanner to query font features.")
    Q_PROPERTY(QString tag READ tag CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(qreal minValue READ minValue CONSTANT)
    Q_PROPERTY(qreal maxValue READ maxValue CONSTANT)
    Q_PROPERTY(qreal defaultValue READ defaultValue CONSTANT)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
private:
    QString m_tag;
    QString m_description;

    qreal m_min;
    qreal m_max;
    qreal m_default;
    qreal m_value;

Q_SIGNALS:
    void valueChanged(qreal newValue);

public:
    VariableAxis(QString &&tag, QString &&description, qreal minValue, qreal maxValue, qreal defaultValue)
        : m_tag(tag)
        , m_description(description)
        , m_min(minValue)
        , m_max(maxValue)
        , m_default(defaultValue)
        , m_value(defaultValue) { };

    const QString &tag() const
    {
        return m_tag;
    }

    const QString &description() const
    {
        return m_description;
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

    qreal value() const
    {
        return m_value;
    }

    void setValue(qreal value)
    {
        if (m_value != value) {
            m_value = value;
            valueChanged(value);
        }
    }
};

inline auto operator<=>(const VariableAxis &lhs, const VariableAxis &rhs)
{
    return lhs.tag() <=> rhs.tag();
}

inline size_t qHash(const VariableAxis &key, size_t seed)
{
    return qHash(key.tag(), seed);
}

class VariableAxisModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Use FontScanner to query font features.")
private:
    QList<VariableAxis *> m_axes;

protected:
    QHash<int, QByteArray> roleNames() const override;

public:
    enum Roles {
        TagRole = Qt::UserRole + 1,
        DescriptionRole,
        ValueRole,
        MinValueRole,
        MaxValueRole,
        DefaultValueRole,
    };

    VariableAxisModel(QList<VariableAxis *> &&axes, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , m_axes(std::move(axes))
    {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};

#endif
