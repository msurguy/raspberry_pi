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
    bool running;
};

#endif // CAMERATHREAD_H
