#ifndef CAMERATHREADCLASS_H
#define CAMERATHREADCLASS_H
#include <QThread>
#include <QProcess>
#include <iostream>

using namespace std;

class CameraThreadClass : public QThread
{
public:
    CameraThreadClass();
    ~CameraThreadClass();

    void setRunning(bool running);

protected:
    void run();

private:
    enum StateMachineType
    {
        STOPPED = 0,
        START = 1,
        RUNNING = 2,
        STOP = 3
    };

    StateMachineType cameraStateMachine;
};

#endif // CAMERATHREAD_H
