#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include <QObject>

class CubeGenerator : public QObject {
    Q_OBJECT
public:
    explicit CubeGenerator(QObject *parent = nullptr);
    Q_INVOKABLE void createCube();
};

#endif // CUBEGENERATOR_H
