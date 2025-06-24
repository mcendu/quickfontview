/*
    SPDX-FileCopyrightText: 2025 Du Yijie <nathandu@outlook.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
#include <KIconTheme>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QUrl>
#include <QtLogging>
#include <QtQml>

int main(int argc, char *argv[])
{
    KIconTheme::initTheme();
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("quickfontview");
    QApplication::setOrganizationName(QStringLiteral("McEndu"));
    QApplication::setOrganizationDomain(QStringLiteral("mcendu.github.io"));
    QApplication::setApplicationName(QStringLiteral("QuickFontView"));
    QApplication::setDesktopFileName(QStringLiteral("info.mcendu.quickfontview"));

    QApplication::setStyle(QStringLiteral("breeze"));
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }

    QCommandLineParser argparse;
    argparse.setApplicationDescription(i18n("Preview fonts."));
    argparse.addHelpOption();
    argparse.addVersionOption();
    argparse.addPositionalArgument(i18n("file"), i18n("The file to open."));

    argparse.process(app);

    const QStringList args = argparse.positionalArguments();

    if (args.count() == 0) {
        // TODO: Implement font list
        qWarning("no font opened");
        return 1;
    }

    auto fontPath = QFileInfo(args.at(0)).absoluteFilePath();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.setInitialProperties({
        {QStringLiteral("file"), fontPath},
    });
    engine.loadFromModule("info.mcendu.quickfontview", "Main");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
