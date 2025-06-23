/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "FontScanner.h"
#include "FontFeatures.h"
#include <QHash>
#include <QSet>
#include <QVarLengthArray>
#include <harfbuzz/hb-ot.h>
#include <harfbuzz/hb.h>

static QSet<QString> scanFeatures(hb_face_t *face);
static QHash<QString, VariableAxis *> scanVariableAxes(hb_face_t *face);

const FontFeatures *scanFontFeatures(hb_blob_t *blob, size_t index)
{
    if (!blob) {
        return nullptr;
    }

    hb_face_t *face = hb_face_create_or_fail(blob, index);
    if (!face) {
        return nullptr;
    }

    auto features = new FontFeatures(scanFeatures(face), scanVariableAxes(face));
    hb_face_destroy(face);
    return features;
}

static QSet<QString> scanFeatures(hb_face_t *face)
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

static QHash<QString, VariableAxis *> scanVariableAxes(hb_face_t *face)
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

const QmlFontFeatures *FontScanner::scan(const QString &path, size_t index)
{
    auto features = scanFontFeatures(path, index);
    if (!features) {
        return nullptr;
    }

    return new QmlFontFeatures(std::move(*features));
}
