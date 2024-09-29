// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "CubeGenerator.h"
#include <QQuickItem>
#include <QQmlComponent>
#include <QQmlEngine>

#include "autogen/environment.h"

void generateCubes(QQmlEngine *engine, QQuickItem *parent, int count)
{
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:/MyCubeModel.qml")));
    for (int i = 0; i < count; ++i) {
        QQuickItem *item = qobject_cast<QQuickItem*>(component.create());
        if (item) {
            item->setParentItem(parent);
            item->setProperty("x", i * 50); // Example positioning
            item->setProperty("y", i * 50);
        }
    }
}

int main(int argc, char *argv[])
{
    set_qt_environment();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(mainQmlFile);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
