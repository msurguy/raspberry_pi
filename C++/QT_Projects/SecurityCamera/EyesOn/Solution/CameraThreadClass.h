#ifndef CAMERATHREADCLASS_H
#define CAMERATHREADCLASS_H
#include <QThread>
#include <QProcess>
#include <QDir>
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
        MONITOR_ONLY = 0,
        START_MOTION = 1,
        RUNNING_MOTION = 2,
        STOP_MOTION = 3
    };

    StateMachineType cameraStateMachine;

    // Motion program vars
    QString motionProgram;
    QProcess *process;

    // Motion program variables for monitor only
    QString monitorOnlyConfPath;
    QStringList monitorOnlyArgs;

    // Motion program variables for motion and monitor
    QString motionConfPath;
    QStringList motionArgs;
};

#endif // CAMERATHREAD_H
