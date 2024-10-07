#include "keyinstancing.h"
#include <iostream>
#include <ostream>

KeyboardInstancing::KeyboardInstancing(){}

KeyboardInstancing::KeyboardInstancing(bool isWhiteNoteArg){
    m_isWhiteNote = isWhiteNoteArg;
}

bool KeyboardInstancing::isWhiteNote() const{
    return m_isWhiteNote;
}


void KeyboardInstancing::setIsWhiteNote(bool isWhiteNote)
{
    if (m_isWhiteNote == isWhiteNote)
        return;

    m_isWhiteNote = isWhiteNote;
    emit isWhiteNoteChanged();
    markDirty();
    m_dirty = true;
}

QByteArray KeyboardInstancing::getInstanceBuffer(int *instanceCount)
{
    std::cout << m_isWhiteNote << std::endl;

    if (m_dirty) {
        m_instanceData.resize(0);

        int instanceNumber = 0;

        for (int note = 0; note <= 127; note++){
            float xPos = note - 60;

            if (utils::isBlackMidiNote(note) && m_isWhiteNote ||
                !utils::isBlackMidiNote(note) && !m_isWhiteNote)
                continue;

            float zScale = 0.5;
            float zPos = -25;
            float yPos = 50;
            float xScale = 0.25;
            if (m_isWhiteNote){
                zScale = 1;
                zPos = -50;
                yPos = 25;
                xScale = 0.4;
            }

            const QVector4D customData{static_cast<float>(note),0,0,0};
            auto entry = calculateTableEntry({ -xPos*25, yPos , zPos -600}, { xScale, 0.5, zScale }, {}, Qt::white, customData);
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
