#ifndef AUDIOMIDI_H
#define AUDIOMIDI_H

#include <QObject>
#include <QQmlEngine>
#include <QtCore/qthread.h>
#include <utils.h>
#include <QList>

class Audiomidi : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QList<bool> pressedNotesList MEMBER pressedNotesList NOTIFY pressedNotesListChanged)
    //Q_PROPERTY(QList<MIDIMessageStruct> midiMessages MEMBER midiMessages NOTIFY midiMessagesChanged)
    Q_PROPERTY(QList<float> midiNotesInfo MEMBER midiNotesInfo NOTIFY midiNotesInfoChanged)
public:
    explicit Audiomidi(QObject *parent = nullptr);
    ~Audiomidi();
    struct MIDIMessageStruct{
        MIDIMessageStruct(){
            eventTime = -1;
            note = -1;
            status = -1;
        }
        MIDIMessageStruct(qint64 eventTimeArg, qint32 noteArg, qint32 statusArg){
            eventTime = eventTimeArg;
            note = noteArg;
            status = statusArg;
        }
        ~MIDIMessageStruct(){};

        qint64 eventTime;
        qint32 note;
        qint32 status;

        bool operator==(const Audiomidi::MIDIMessageStruct& other) const {
            return other.eventTime == eventTime && other.note == note && other.status == status;
        }
    };
public slots:
    void debug();
    void readMidiData (QString filename);
signals:
    void pressedNotesListChanged();
    void midiNotesInfoChanged();
protected:
    QThread midiThread{};
    QThread audioThread{};
    QList<bool> pressedNotesList;
    QList<MIDIMessageStruct> midiMessages;
    QList<float> midiNotesInfo;
};

Q_DECLARE_METATYPE(Audiomidi::MIDIMessageStruct)

#endif // AUDIOMIDI_H
