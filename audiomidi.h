#ifndef AUDIOMIDI_H
#define AUDIOMIDI_H

#include <QObject>
#include <QQmlEngine>
#include <QtCore/qthread.h>

class Audiomidi : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Audiomidi(QObject *parent = nullptr);

public slots:
    void handleButtonClick(const double freq);

protected:
    QThread thread{};

};
#endif // AUDIOMIDI_H
