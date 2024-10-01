#ifndef TEST_H
#define TEST_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QQmlComponent>
#include <QQmlEngine>


class Test {
    QML_ELEMENT
    QML_UNCREATABLE("")

public:
    void createMyCube(){
        QQmlApplicationEngine engine;
        QQmlComponent component(&engine,
                                QUrl::fromLocalFile("qml/DesignerProjectContent/MyCubeModel.qml"));
        if (component.isReady()){
            QObject *object = component.create();
            qDebug() << object->property("x");
        }
        else qDebug() << component.errorString();

    }
};
#endif // TEST_H
