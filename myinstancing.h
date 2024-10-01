#ifndef MYINSTANCING_H
#define MYINSTANCING_H

#include <QtQuick3D/qquick3dinstancing.h>
//! [properties]
class MyInstancing : public QQuick3DInstancing
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MyInstancing(QQuick3DObject *parent = nullptr);
    ~MyInstancing() override;
protected:
    QByteArray getInstanceBuffer(int *instanceCount) override;
private:
    int m_instanceCount = 0;
    bool m_dirty = true;
    QByteArray m_instanceData;
    float m_spacing = 20;
};
#endif // MYINSTANCING_H
