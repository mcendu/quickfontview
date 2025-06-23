/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include "FontFeatures.h"

#include <QHash>

size_t qHash(const VariableAxis &key, size_t seed)
{
    return qHash(key.tag(), seed);
}
