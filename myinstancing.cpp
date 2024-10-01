#include "./myinstancing.h"
#include <math.h>
#include <QColor>

MyInstancing::MyInstancing(QQuick3DObject *parent) : QQuick3DInstancing(parent)
{
}
MyInstancing::~MyInstancing()
{
}

QByteArray MyInstancing::getInstanceBuffer(int *instanceCount)
{
    if (m_dirty) {
        m_instanceData.resize(0);

        //auto idxToPos = [this](int i) -> float { return m_gridSpacing * (i - m_gridSize / 2); };

        int instanceNumber = 0;
        for (int i = 0; i<3; i++){
            qDebug() << "cretng";
            float yPos = i*20;
            auto entry = calculateTableEntry({ 0, yPos, 0 }, { 1.0, 1.0, 1.0 }, {}, Qt::white, {});
            m_instanceData.append(reinterpret_cast<const char *>(&entry), sizeof(entry));
            instanceNumber++;
        }

        m_instanceCount = instanceNumber;
        m_dirty = false;
    }
    if (instanceCount)
        *instanceCount = m_instanceCount;

    return m_instanceData;

}
