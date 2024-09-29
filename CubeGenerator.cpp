#include "CubeGenerator.h"
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>

#include <QDebug>
#include <QString>


CubeGenerator::CubeGenerator(QObject *parent) : QObject(parent) {}

void CubeGenerator::createCube() {

    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:qt/qml/DesignerProjectContent/MyCubeModel.qml")));
    if (component.isReady()) {
        QObject *object = component.create();
        // Optionally, you can manipulate the object here
    } else {
        qWarning() << component.errors();
    }
}
