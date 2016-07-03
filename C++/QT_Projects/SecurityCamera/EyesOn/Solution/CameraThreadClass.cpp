#include "CameraThreadClass.h"

//
// Constructor

//
CameraThreadClass::CameraThreadClass()
{
    cout << "Camera Thread Started" << endl;
    this->cameraStateMachine = MONITOR_ONLY;

    // Motion program vars
    this->motionProgram = "motion";

    // Monitor only vars
    this->monitorOnlyConfPath = QDir::currentPath() + "/motion_monitorOnly.conf";
    this->monitorOnlyArgs << "-c" << this->monitorOnlyConfPath;

    // Motion and monitor vars
    this->motionConfPath = QDir::currentPath() + "/motion_Movement.conf";
    this->motionArgs << "-c" << this->motionConfPath;

    // Start the monitor only process
    cout << "Starting motion only" << endl;
    this->process = new QProcess();
    this->process->start(this->motionProgram, this->monitorOnlyArgs);
} // CameraThreadClass()

//
// Destructor
//
CameraThreadClass::~CameraThreadClass()
{
    if(this->process)
    {
        cout << "Stopping monitor" << endl;
        this->process->close();
        this->process->waitForFinished(0);
        delete this->process;
    }

    cout << "Camera Thread Ended" << endl;
} // ~CameraThreadClass()

//
// Run the Camera Thread
//
void CameraThreadClass::run()
{

    while(true)
    {
        switch(this->cameraStateMachine)
        {
        case START_MOTION:
            // Stop the monitor only
            cout << "Stopping monitor only" << endl;
            this->process->close();
            delete this->process;

            cout << "Starting Motion and monitor" << endl;
            this->process = new QProcess();
            this->process->start(this->motionProgram, this->motionArgs);
            this->cameraStateMachine = RUNNING_MOTION;
            break;
        case STOP_MOTION:
            cout << "Stopping Motion and monitor" << endl;
            this->process->close();
            delete this->process;

            // Start the monitor only process
            cout << "Starting monitor only" << endl;
            this->process = new QProcess();
            this->process->start(this->motionProgram, this->monitorOnlyArgs);
            this->cameraStateMachine = MONITOR_ONLY;
            break;
        case RUNNING_MOTION:
            //cout << "Motion Capture running" << endl;
            //sleep(5);
            break;
        case MONITOR_ONLY:
            //sleep(5);
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
        this->cameraStateMachine = START_MOTION;
    }
    else
    {
        this->cameraStateMachine = STOP_MOTION;
    }
} // setRunning()
