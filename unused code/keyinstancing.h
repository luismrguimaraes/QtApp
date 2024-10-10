#ifndef KEYINSTANCING_H
#define KEYINSTANCING_H

#include <QtQuick3D/qquick3dinstancing.h>
#include <utils.h>

class KeyboardInstancing : public QQuick3DInstancing
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool isWhiteNote READ isWhiteNote WRITE setIsWhiteNote NOTIFY isWhiteNoteChanged)
    Q_PROPERTY(QList<bool> pressedNotesList READ pressedNotesList WRITE setPressedNotesList NOTIFY pressedNotesListChanged)
public:
    KeyboardInstancing();
    //KeyboardInstancing(bool isWhiteNote);
    QByteArray m_instanceData;
    int m_instanceCount = 0;

    bool isWhiteNote() const;
    QList<bool> pressedNotesList() const;
public slots:
    void setIsWhiteNote(bool isWhiteNote);
    void setPressedNotesList(QList<bool> pressedNotesList);
signals:
    void isWhiteNoteChanged();
    void pressedNotesListChanged();
protected:
    QByteArray getInstanceBuffer(int *instanceCount) override;
private:
    bool m_dirty = true;
    bool m_isWhiteNote = true;
    QList<bool> m_pressedNotesList;
};

#endif // KEYINSTANCING_H
