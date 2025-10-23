/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#ifndef QFV_DESCRIPTIONS_H
#define QFV_DESCRIPTIONS_H

#include <QHash>
#include <QString>
#include <KLocalizedString>

/** Table of human-readable feature tag descriptions. */
extern const QHash<QString, KLocalizedString> featureTagDescriptions;

/** Table of human-readable variation axis descriptions. */
extern const QHash<QString, KLocalizedString> axisDescriptions;

#endif
