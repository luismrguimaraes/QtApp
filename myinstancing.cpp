#include "./myinstancing.h"
#include <math.h>


MyInstancing::MyInstancing(QQuick3DObject *parent) : QQuick3DInstancing(parent)
{
}
MyInstancing::~MyInstancing()
{
}

QByteArray MyInstancing::getInstanceBuffer(int *instanceCount)
{

    m_instanceData.resize(0);
    *instanceCount = 0;
    return m_instanceData;

    /*
    if (m_dirty) {
        BlockTable blocks(m_gridSize, m_randomSeed);
        m_instanceData.resize(0);

        auto idxToPos = [this](int i) -> float { return m_gridSpacing * (i - m_gridSize / 2); };

        int instanceNumber = 0;
        for (int i = 0; i < m_gridSize; ++i) {
            float xPos = idxToPos(i);
            for (int j = 0; j < m_gridSize; ++j) {
                float zPos = idxToPos(j);
                int lowest = blocks.lowestVisible(i, j);
                int highest = blocks.highestBlock(i, j);
                for (int k = lowest; k <= highest; ++k) {
                    float yPos = idxToPos(k);
                    QColor color = blocks.getBlockColor(i, j, k);
                    float waterAnimation = blocks.isWaterSurface(i, j, k) ? 1.0 : 0.0;
                    auto entry = calculateTableEntry({ xPos, yPos, zPos }, { 1.0, 1.0, 1.0 }, {}, color, { waterAnimation, 0, 0, 0 });
                    m_instanceData.append(reinterpret_cast<const char *>(&entry), sizeof(entry));
                    instanceNumber++;
                }
            }
        }
        m_instanceCount = instanceNumber;
        m_dirty = false;
    }
    if (instanceCount)
        *instanceCount = m_instanceCount;

    return m_instanceData;
*/
}
