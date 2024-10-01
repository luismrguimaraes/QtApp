#ifndef AUDIOMIDI_H
#define AUDIOMIDI_H

#include <QObject>
#include <QQmlEngine>
#include "libs/rtaudio/RtAudio.h"

class audiomidi : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit audiomidi(QObject *parent = nullptr);

signals:

};
#endif // AUDIOMIDI_H
