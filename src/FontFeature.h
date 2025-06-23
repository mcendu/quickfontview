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

class FontFeatureModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Use FontScanner to query font features.")
private:
    QList<QString> m_features;

protected:
    QHash<int, QByteArray> roleNames() const override;

public:
    enum Roles {
        TagRole = Qt::UserRole + 1,
    };

    FontFeatureModel(QList<QString> &&tags, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , m_features(std::move(tags))
    {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif
