/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_FONTFEATUREMODEL_H
#define QFV_FONTFEATUREMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QtQmlIntegration>
#include <utility>

/**
 * An OpenType feature available in a font.
 */
class FontFeature : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tag READ tag CONSTANT)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY statusChanged)
    Q_PROPERTY(QString description READ description CONSTANT)
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

    /**
     * Get the feature's tag.
     */
    const QString &tag() const
    {
        return m_tag;
    }

    /**
     * Get the human-readable description of the feature.
     */
    QString description() const;

    /**
     * Get whether the feature is enabled.
     */
    bool enabled() const
    {
        return m_enabled;
    }

    /**
     * Enable or disable the feature.
     */
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
        DescriptionRole,
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
