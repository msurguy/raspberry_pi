#include "CameraThreadClass.h"

CameraThreadClass::CameraThreadClass()
{
    cout << "Camera Thread Started" << endl;
    this->running = false;
}

CameraThreadClass::~CameraThreadClass()
{
    cout << "Camera Thread Ended" << endl;
}

void CameraThreadClass::run()
{
    // Test
    QString program = "fswebcam";
    QStringList args;
    args << "-r" << "640x480" << "/home/pi/Desktop/SecurityCam/currentImage.jpg";
    QProcess *process = new QProcess();

    while(true)
    {
        if(this->running)
        {
            cout << "Camera Thread running" << endl;
            process->start(program, args);
            process->waitForFinished(-1);
            process->close();
            sleep(1);
        }
        else
        {
            sleep(5);
        }
    }

}


void CameraThreadClass::setRunning(bool running)
{
    this->running = running;
}
