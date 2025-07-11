/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "FontScanner.h"

#include "FontFeature.h"
#include "VariableAxis.h"
#include <QHash>
#include <QSet>
#include <QVarLengthArray>
#include <algorithm>
#include <harfbuzz/hb-ot.h>
#include <harfbuzz/hb.h>
#include <utility>

static auto featurePtrLess(const FontFeature *lhs, const FontFeature *rhs)
{
    return lhs->tag() < rhs->tag();
}

const FontFeatureModel *FontScanner::scanFeatures(const QString &path, size_t index)
{
    hb_face_t *face = hb_face_create_from_file_or_fail(path.toLocal8Bit().data(), index);
    if (!face) {
        return new FontFeatureModel(QList<FontFeature *>());
    }

    auto featureTags = scanFeaturesRaw(face).values();
    hb_face_destroy(face);

    auto features = QList<FontFeature *>();
    features.reserve(featureTags.size());
    for (const QString &i : featureTags) {
        features.append(new FontFeature(i));
    }

    std::sort(features.begin(), features.end(), featurePtrLess);
    return new FontFeatureModel(std::move(features));
}

QSet<QString> FontScanner::scanFeaturesRaw(hb_face_t *face)
{
    constexpr unsigned int maxCount = 32;

    QSet<QString> features;
    hb_tag_t featureTags[maxCount];
    unsigned int count = maxCount;
    unsigned int offset = 0;

    do {
        hb_ot_layout_table_get_feature_tags(face, HB_OT_TAG_GSUB, offset, &count, featureTags);
        for (size_t i = 0; i < count; ++i) {
            char tag[4];
            hb_tag_to_string(featureTags[i], tag);
            features.insert(QString::fromLatin1(tag, 4));
        }
        offset += count;
    } while (count != 0);

    return features;
}

static auto axisPtrLess(const VariableAxis *lhs, const VariableAxis *rhs)
{
    return *lhs < *rhs;
}

const VariableAxisModel *FontScanner::scanVariableAxes(const QString &path, size_t index)
{
    hb_face_t *face = hb_face_create_from_file_or_fail(path.toLocal8Bit().data(), index);
    if (!face) {
        return new VariableAxisModel(QList<VariableAxis *>());
    }

    auto axes = scanVariableAxesRaw(face).values();
    hb_face_destroy(face);
    std::sort(axes.begin(), axes.end(), axisPtrLess);
    return new VariableAxisModel(std::move(axes));
}

QHash<QString, VariableAxis *> FontScanner::scanVariableAxesRaw(hb_face_t *face)
{
    if (!hb_ot_var_has_data(face))
        return QHash<QString, VariableAxis *>{};

    auto count = hb_ot_var_get_axis_count(face);
    QVarLengthArray<hb_ot_var_axis_info_t> axisInfos(count);
    hb_ot_var_get_axis_infos(face, 0, &count, axisInfos.data());

    QHash<QString, VariableAxis *> axes;

    for (const hb_ot_var_axis_info_t &i : axisInfos) {
        char ctag[4];
        hb_tag_to_string(i.tag, ctag);
        auto tag = QString::fromLatin1(ctag, 4);

        axes.insert(tag, new VariableAxis(tag, i.min_value, i.max_value, i.default_value));
    }

    return axes;
}
