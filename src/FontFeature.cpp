/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "FontFeature.h"

QHash<int, QByteArray> FontFeatureModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TagRole] = "tag";
    return roles;
}

int FontFeatureModel::rowCount(const QModelIndex &) const {
    return m_features.count();
}

QVariant FontFeatureModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_features.count()) {
        return QVariant();
    }

    if (role == TagRole) {
        return m_features.at(index.row());
    } else {
        return QVariant();
    }
}
