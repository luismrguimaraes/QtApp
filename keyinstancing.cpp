#include "keyinstancing.h"
#include <QtQml/qqmlapplicationengine.h>

KeyboardInstancing::KeyboardInstancing(){}

//KeyboardInstancing::KeyboardInstancing(bool isWhiteNoteArg){
//    m_isWhiteNote = isWhiteNoteArg;
    //m_pressedNotesList = pressedNotesList;
//}

bool KeyboardInstancing::isWhiteNote() const{
    return m_isWhiteNote;
}
QList<bool> KeyboardInstancing::pressedNotesList() const{
    return m_pressedNotesList;
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
void KeyboardInstancing::setPressedNotesList(QList<bool> pressedNotesList){
    if (m_pressedNotesList == pressedNotesList)
        return;

    m_pressedNotesList = pressedNotesList;
    emit pressedNotesListChanged();
    markDirty();
    m_dirty = true;
}

QByteArray KeyboardInstancing::getInstanceBuffer(int *instanceCount)
{
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
            float yPos = 100;
            float xScale = 0.25;
            if (m_isWhiteNote){
                zScale = 1;
                zPos = -50;
                yPos = 80;
                xScale = 0.4;
            }

            QColor color = Qt::white;
            if (m_pressedNotesList[note]){
                yPos -= 20;
                color = Qt::green;
            }

            const QVector4D customData{static_cast<float>(note),0,0,0};
            auto entry = calculateTableEntry({ -xPos*25, yPos , zPos -500}, { xScale, 1, zScale }, {}, color, customData);
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
