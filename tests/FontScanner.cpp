/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include <FontScanner.h>

#include <QObject>
#include <QTest>
#include <harfbuzz/hb.h>

class testFontScanner : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void enumerate();
    void variableFont();
};

void testFontScanner::enumerate()
{
    hb_face_t *face = hb_face_create_from_file_or_fail("resources/NotoSans-Regular.ttf", 0);
    QVERIFY(face);
    auto features = FontScanner::scanFeaturesRaw(face);
    hb_face_destroy(face);

    QVERIFY(!features.isEmpty());
    QVERIFY(features.contains(QString::fromUtf8(u8"liga")));
}

void testFontScanner::variableFont()
{
    hb_face_t *face = hb_face_create_from_file_or_fail("resources/RobotoFlex.ttf", 0);
    QVERIFY(face);
    auto features = FontScanner::scanFeaturesRaw(face);
    auto axes = FontScanner::scanVariableAxesRaw(face);
    hb_face_destroy(face);

    QVERIFY(!features.isEmpty());
    QVERIFY(features.contains(QString::fromUtf8(u8"liga")));
    QVERIFY(!axes.isEmpty());
    QVERIFY(axes.contains(QString::fromUtf8(u8"wght")));
    QVERIFY(axes.contains(QString::fromUtf8(u8"GRAD")));
}

QTEST_MAIN(testFontScanner)
#include "FontScanner.moc"
