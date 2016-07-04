#include "CameraThreadClass.h"

//
// Constructor

//
CameraThreadClass::CameraThreadClass(SettingsClass Settings)
{
    cout << "Camera Thread Started" << endl;
    this->cameraStateMachine = MONITOR_ONLY;

    // Motion program vars
    this->motionProgram = "motion";

    // Monitor only vars
    this->monitorOnlyArgs << "-c" << Settings.monitorOnlyConfPath;

    // Motion and monitor vars
    this->motionArgs << "-c" << Settings.motionConfPath;

    // Start the monitor only process
    cout << "Starting monitor only" << endl;
    this->process = new QProcess();
    this->process->start(this->motionProgram, this->monitorOnlyArgs);
} // CameraThreadClass()

//
// Destructor
//
CameraThreadClass::~CameraThreadClass()
{
    sleep(1);
    if(this->process)
    {
        cout << "Stopping motion process" << endl;
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
            cout << "   Stopping monitor only" << endl;
            this->process->close();
            delete this->process;

            cout << "   Starting Motion and monitor" << endl;
            this->process = new QProcess();
            this->process->start(this->motionProgram, this->motionArgs);
            this->cameraStateMachine = RUNNING_MOTION;
            break;
        case STOP_MOTION:
            cout << "   Stopping Motion and monitor" << endl;
            this->process->close();
            delete this->process;

            // Start the monitor only process
            cout << "   Starting monitor only" << endl;
            this->process = new QProcess();
            this->process->start(this->motionProgram, this->monitorOnlyArgs);
            this->cameraStateMachine = MONITOR_ONLY;
            break;
        case RUNNING_MOTION:
            break;
        case MONITOR_ONLY:
            break;
        case QUIT:
            return;
        }
        sleep(1);
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

//
// Stop all monitoring and get ready to quit the thread
//
void CameraThreadClass::stopAll()
{
    this->cameraStateMachine = QUIT;
}
