/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "FontFeature.h"

#include "Descriptions.h"
#include <QStringView>

QString FontFeature::description() const
{
    // special case Character Variant and Stylistic Set tags to reduce
    // translator burden
    if (m_tag.startsWith(QStringLiteral("cv"))) {
        // check validity of cv.. tag
        bool isCharacterVariantTag;
        int variant = QStringView(m_tag).sliced(2).toInt(&isCharacterVariantTag);
        if (!isCharacterVariantTag)
            return QString(m_tag);

        return featureTagDescriptions[QStringLiteral("cv01")].toString().arg(variant);
    } else if (m_tag.startsWith(QStringLiteral("ss"))) {
        // check validity of ss.. tag
        bool isStylisticSetTag;
        int set = QStringView(m_tag).sliced(2).toInt(&isStylisticSetTag);
        // OpenType standard only defines ss01 - ss20
        if (!isStylisticSetTag || set > 20)
            return QString(m_tag);

        return featureTagDescriptions[QStringLiteral("ss01")].toString().arg(set);
    }

    auto s = featureTagDescriptions.find(m_tag);
    // bail out to the tag name for unknown tags
    if (s == featureTagDescriptions.end())
        return QString(m_tag);
    return s.value().toString();
}

QHash<int, QByteArray> FontFeatureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TagRole] = "tag";
    roles[DescriptionRole] = "description";
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
    } else if (role == DescriptionRole) {
        return row->description();
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
