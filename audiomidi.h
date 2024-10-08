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
public:
    explicit Audiomidi(QObject *parent = nullptr);
public slots:
    void debug();
signals:
    void pressedNotesListChanged();
protected:
    QThread midiThread{};
    QThread audioThread{};
    QList<bool> pressedNotesList;
};
#endif // AUDIOMIDI_H
