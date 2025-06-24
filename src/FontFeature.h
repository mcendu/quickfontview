/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_FONTFEATUREMODEL_H
#define QFV_FONTFEATUREMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QtQmlIntegration>
#include <qcontainerfwd.h>
#include <utility>

class FontFeature : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tag READ tag CONSTANT)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY statusChanged)
private:
    QString m_tag;
    bool m_enabled;

Q_SIGNALS:
    void statusChanged(bool enabled);

public:
    FontFeature(const QString &tag)
        : m_tag(tag)
        , m_enabled(false)
    {
    }

    const QString &tag() const
    {
        return m_tag;
    }

    bool enabled() const
    {
        return m_enabled;
    }

    void setEnabled(bool enabled)
    {
        if (m_enabled != enabled) {
            m_enabled = enabled;
            statusChanged(enabled);
        }
    }
};

class FontFeatureModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Use FontScanner to query font features.")
private:
    QList<FontFeature *> m_features;

protected:
    QHash<int, QByteArray> roleNames() const override;

public:
    enum Roles {
        TagRole = Qt::UserRole + 1,
        EnabledRole,
    };

    FontFeatureModel(QList<FontFeature *> &&tags, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , m_features(std::move(tags))
    {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};

#endif
