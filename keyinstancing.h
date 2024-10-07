#ifndef KEYINSTANCING_H
#define KEYINSTANCING_H

#include <QtQuick3D/qquick3dinstancing.h>
#include <utils.h>

class KeyboardInstancing : public QQuick3DInstancing
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool isWhiteNote READ isWhiteNote WRITE setIsWhiteNote NOTIFY isWhiteNoteChanged)
public:
    KeyboardInstancing();
    KeyboardInstancing(bool isWhiteNote);

    bool isWhiteNote() const;
public slots:
    void setIsWhiteNote(bool isWhiteNote);
signals:
    void isWhiteNoteChanged();
protected:
    QByteArray getInstanceBuffer(int *instanceCount) override;
private:
    int m_instanceCount = 0;
    bool m_dirty = true;
    QByteArray m_instanceData;
    bool m_isWhiteNote = true;
};

#endif // KEYINSTANCING_H
