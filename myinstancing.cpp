#include "./myinstancing.h"
#include "libs/QMidi/src/QMidiFile.h"
#include <QtCore/qthread.h>
#include <math.h>
#include <QColor>
#include <iostream>

MyInstancing::MyInstancing(QQuick3DObject *parent) : QQuick3DInstancing(parent)
{
    QMidiFile* midi_file = new QMidiFile();
    midi_file->load(":/test.mid");

    QList<QMidiEvent*> events = midi_file->events();
    std::cout << "Reading MIDI file ..." << std::endl;
    for (QMidiEvent* e : events) {
        if (e->type() != QMidiEvent::Meta) {
            qint64 eventTime = midi_file->timeFromTick(e->tick()) *1000;

            if (e->type() != QMidiEvent::SysEx) {
                qint32 message = e->message();

                qint32 status = message & 0x0000F0;
                qint32 channel = message & 0x00000F;

                if (status == 144 && channel == 0){
                    // note on
                    qint32 note = (message & 0x00FF00) >> 8;
                    //qint32 velocity = (message & 0xFF0000) >> 8*2;

                    MIDIMessageStruct newMessage {eventTime, note, status};
                    messages.append(newMessage);

                }
                if (status == 128 && channel == 0){
                    // note off
                    qint32 note = (message & 0x00FF00) >> 8;

                    MIDIMessageStruct newMessage {eventTime, note, status};
                    messages.append(newMessage);
                }
            }
        }
    }
}
MyInstancing::~MyInstancing()
{
}

QByteArray MyInstancing::getInstanceBuffer(int *instanceCount)
{
    if (m_dirty) {
        m_instanceData.resize(0);

        int instanceNumber = 0;

        // iterate messages
        for (qsizetype i = 0; i < messages.size(); ++i) {
            auto status = messages.at(i).status;

            if (status == 144){
                // note on: search note off
                auto noteOnTimeInSecs = messages.at(i).eventTime/1000.0;
                double noteDurationInSecs = 0;

                float xPos = messages.at(i).note - 60; // 60 being C3

                for (qsizetype j = i; j < messages.size(); ++j){
                    if (messages.at(j).status == 128 && messages.at(j).note == messages.at(i).note){
                        // note off
                        noteDurationInSecs = messages.at(j).eventTime/1000.0 - noteOnTimeInSecs;
                        break;
                    }
                }

                float zScale = noteDurationInSecs / 2;
                float zPos = noteOnTimeInSecs + noteDurationInSecs/2;

                float xScale = 0.25;
                QColor color = QColorConstants::White;
                if (utils::isBlackMidiNote(messages.at(i).note)){
                    xScale *= 0.5;
                    color = QColorConstants::Black;
                }

                const QVector4D customData{static_cast<float>(messages.at(i).note),0,0,0};
                auto entry = calculateTableEntry({ -xPos*25, 0, zPos*50}, { xScale, 0.25, zScale }, {}, color, customData);
                m_instanceData.append(reinterpret_cast<const char *>(&entry), sizeof(entry));
                instanceNumber++;
            }
        }

        m_instanceCount = instanceNumber;
        m_dirty = false;
    }
    if (instanceCount)
        *instanceCount = m_instanceCount;

    std::cout << m_instanceCount << std::endl;

    return m_instanceData;

}
