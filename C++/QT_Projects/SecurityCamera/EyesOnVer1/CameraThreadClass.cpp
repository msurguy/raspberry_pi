#include "CameraThreadClass.h"

//
// Constructor

//
CameraThreadClass::CameraThreadClass()
{
    cout << "Camera Thread Started" << endl;
    this->cameraStateMachine = STOPPED;
} // CameraThreadClass()

//
// Destructor
//
CameraThreadClass::~CameraThreadClass()
{
    cout << "Camera Thread Ended" << endl;
} // ~CameraThreadClass()

//
// Run the Camera Thread
//
void CameraThreadClass::run()
{
    // Using FSWebcam
    QString program = "motion";

    QProcess *process = new QProcess();

    while(true)
    {
        switch(this->cameraStateMachine)
        {
        case START:
            cout << "Starting Motion Capture software" << endl;
            process->start(program);
            this->cameraStateMachine = RUNNING;
            break;
        case STOP:
            cout << "Stopping Motion Capture software" << endl;
            process->close();
            this->cameraStateMachine = STOPPED;
            break;
        case RUNNING:
            cout << "Motion Capture software running" << endl;
            sleep(5);
            break;
        case STOPPED:
            sleep(5);
            break;
        }
    } // while true

} // run()

//
// Set the Camera to running
//
void CameraThreadClass::setRunning(bool running)
{
    if(running)
    {
        this->cameraStateMachine = START;
    }
    else
    {
        this->cameraStateMachine = STOP;
    }
} // setRunning()
