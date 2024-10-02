#ifndef AUDIOMIDI_H
#define AUDIOMIDI_H

#include <QObject>
#include <QQmlEngine>

class Audiomidi : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Audiomidi(QObject *parent = nullptr);

public slots:
    void handleButtonClick(const double freq);


};
#endif // AUDIOMIDI_H
