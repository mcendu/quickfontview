/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include <FontScanner.h>

#include <QTest>
#include <QObject>
#include <qtestcase.h>

class testFontScanner : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void enumerate();
    void variableFont();
};

void testFontScanner::enumerate()
{
    auto features = scanFontFeatures("resources/NotoSans-Regular.ttf", 0);
    QCOMPARE_NE(features.get(), nullptr);
    QVERIFY(!features->features().isEmpty());
    QVERIFY(features->features().contains(QString::fromUtf8(u8"liga")));
}

void testFontScanner::variableFont()
{
    auto features = scanFontFeatures("resources/RobotoFlex.ttf", 0);
    QCOMPARE_NE(features.get(), nullptr);
    QVERIFY(!features->features().isEmpty());
    QVERIFY(features->features().contains(QString::fromUtf8(u8"liga")));
    QVERIFY(!features->axes().isEmpty());
    QVERIFY(features->axes().contains(QString::fromUtf8(u8"wght")));
    QVERIFY(features->axes().contains(QString::fromUtf8(u8"GRAD")));
}

QTEST_MAIN(testFontScanner)
#include "FontScanner.moc"
