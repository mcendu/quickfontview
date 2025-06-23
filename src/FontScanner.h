/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_FONTSCANNER_H
#define QFV_FONTSCANNER_H

#include "FontFeatures.h"
#include <QString>
#include <QVariant>
#include <harfbuzz/hb.h>

const FontFeatures *scanFontFeatures(hb_blob_t *blob, size_t index);

inline const FontFeatures *scanFontFeatures(const void *blob, size_t size, size_t index)
{
    return scanFontFeatures(hb_blob_create_or_fail((const char *)blob, size, HB_MEMORY_MODE_READONLY, nullptr, nullptr), index);
}

inline const FontFeatures *scanFontFeatures(const char *path, size_t index)
{
    return scanFontFeatures(hb_blob_create_from_file_or_fail(path), index);
}

inline const FontFeatures *scanFontFeatures(const QString &path, size_t index)
{
    return scanFontFeatures(path.toLocal8Bit().data(), index);
}

#endif
