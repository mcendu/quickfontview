/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "VariableAxis.h"

QHash<int, QByteArray> VariableAxisModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TagRole] = "tag";
    roles[DescriptionRole] = "description";
    roles[ValueRole] = "value";
    roles[MinValueRole] = "minValue";
    roles[MaxValueRole] = "maxValue";
    roles[DefaultValueRole] = "defaultValue";
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
    case DescriptionRole:
        return axis->description();
    case ValueRole:
        return axis->value();
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

bool VariableAxisModel::setData(const QModelIndex &index, const QVariant &variant, int role)
{
    if (!index.isValid())
        return false;

    if (index.row() >= m_axes.count()) {
        return false;
    }

    if (role == ValueRole) {
        bool isNumber;
        qreal value = variant.toReal(&isNumber);

        if (!isNumber)
            return false;

        m_axes.at(index.row())->setValue(value);
        dataChanged(index, index, QList<int>{ValueRole});
        return true;
    } else {
        return false;
    }
}
