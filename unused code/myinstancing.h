#ifndef MYINSTANCING_H
#define MYINSTANCING_H

#include <QtQuick3D/qquick3dinstancing.h>
#include <utils.h>
//! [properties]
class MyInstancing : public QQuick3DInstancing
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MyInstancing(QQuick3DObject *parent = nullptr);
    ~MyInstancing() override;
    struct MIDIMessageStruct{
        MIDIMessageStruct(qint64 eventTimeArg, qint32 noteArg, qint32 statusArg){
            eventTime = eventTimeArg;
            note = noteArg;
            status = statusArg;
        }
        ~MIDIMessageStruct(){};

        qint64 eventTime;
        qint32 note;
        qint32 status;
    };

protected:
    QByteArray getInstanceBuffer(int *instanceCount) override;
private:
    int m_instanceCount = 0;
    bool m_dirty = true;
    QByteArray m_instanceData;
    QList<MIDIMessageStruct> messages;

};
#endif // MYINSTANCING_Ha
