/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "FontFeature.h"

QHash<int, QByteArray> FontFeatureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TagRole] = "tag";
    roles[EnabledRole] = "enabled";
    return roles;
}

int FontFeatureModel::rowCount(const QModelIndex &) const
{
    return m_features.count();
}

QVariant FontFeatureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_features.count()) {
        return QVariant();
    }

    auto row = m_features.at(index.row());

    if (role == TagRole) {
        return row->tag();
    } else if (role == EnabledRole) {
        return row->enabled();
    } else {
        return QVariant();
    }
}

bool FontFeatureModel::setData(const QModelIndex &index, const QVariant &variant, int role)
{
    if (!index.isValid())
        return false;

    if (index.row() >= m_features.count()) {
        return false;
    }

    if (role == EnabledRole) {
        bool value = variant.toBool();

        m_features.at(index.row())->setEnabled(value);
        dataChanged(index, index, QList<int>{EnabledRole});
        return true;
    } else {
        return false;
    }
}
