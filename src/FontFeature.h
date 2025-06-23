/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_FONTFEATUREMODEL_H
#define QFV_FONTFEATUREMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <utility>

class FontFeatureModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<QString> m_features;

public:
    enum Roles {
        TagRole = Qt::UserRole + 1,
    };

    FontFeatureModel(QList<QString> &&tags, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , m_features(std::move(tags))
    {
    }

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif
