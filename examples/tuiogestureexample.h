#ifndef TUIOGESTUREEXAMPLE_H
#define TUIOGESTUREEXAMPLE_H

#include <QObject>

#include <OutputDevice.h>

class TuioGestureExample;
class QGesture;

namespace KetaRoller {
class InputDevice;
class InputPort;
class OutputPort;
}

class TestOutputDevice : public KetaRoller::OutputDevice
{
    Q_OBJECT
public:
    TestOutputDevice(TuioGestureExample* parent = 0);
    virtual ~TestOutputDevice();

    virtual void init(const QVariantMap& args = QVariantMap());
    virtual bool validatePort(KetaRoller::OutputPort* port);

public slots:
    void newDataFromPort(KetaRoller::OutputPort *port, QGesture *gesture);

private:
    QHash<int, QTime> m_times;
    TuioGestureExample *q;
};

class TuioGestureExample : public QObject
{
Q_OBJECT
public:
    explicit TuioGestureExample(QObject *parent = 0);



signals:

public slots:

private:
    KetaRoller::InputDevice *m_device;
    TestOutputDevice *m_outputDevice;
};

#endif // TUIOGESTUREEXAMPLE_H
