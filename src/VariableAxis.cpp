/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "VariableAxis.h"

QHash<int, QByteArray> VariableAxisModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TagRole] = "tag";
    roles[MinValueRole] = "min";
    roles[MaxValueRole] = "max";
    roles[DefaultValueRole] = "default";
    return roles;
}

int VariableAxisModel::rowCount(const QModelIndex &) const
{
    return m_axes.count();
}

QVariant VariableAxisModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_axes.count()) {
        return QVariant();
    }

    VariableAxis *axis = m_axes.at(index.row());

    switch (role) {
    case TagRole:
        return axis->tag();
    case MinValueRole:
        return axis->minValue();
    case MaxValueRole:
        return axis->maxValue();
    case DefaultValueRole:
        return axis->defaultValue();
    default:
        return QVariant();
    }
}
