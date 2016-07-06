#include "CameraThreadClass.h"

//
// Constructor

//
CameraThreadClass::CameraThreadClass(QObject* parent, SettingsClass Settings, QTextEdit *tbxStatus)
{
    this->setParent(parent);
    this->tbxStatus = tbxStatus;

    cout << "Camera Thread Started" << endl;
    this->tbxStatus->append("Camera Thread Started");
    this->cameraStateMachine = MONITOR_ONLY;

    // Motion program vars
    this->motionProgram = "motion";

    // Monitor only vars
    this->monitorOnlyArgs << "-c" << Settings.monitorOnlyConfPath;

    // Motion and monitor vars
    this->motionArgs << "-c" << Settings.motionConfPath;

    // Start the monitor only process
    cout << "Starting monitor only" << endl;
    this->tbxStatus->append("Starting monitor only");
    this->process = new QProcess();

    while(this->process->state() != QProcess::Running)
    {
        this->process->start(this->motionProgram, this->monitorOnlyArgs);
        this->process->waitForStarted(-1);
    }
} // CameraThreadClass()

//
// Destructor
//
CameraThreadClass::~CameraThreadClass()
{
    sleep(1);
    if(this->process)
    {
        this->tbxStatus->append("Stopping Motion process");
        this->process->close();
        this->process->kill();
        this->process->waitForFinished(0);
        delete this->process;
    }

    this->tbxStatus->append("Camera Thread Ended");
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
            this->tbxStatus->append("--Stopping Monitor");
            this->process->close();
            this->process->waitForFinished();
            delete this->process;


            this->tbxStatus->append("--Starting Motion Detection");
            this->process = new QProcess();

            while(this->process->state() != QProcess::Running)
            {
                this->process->start(this->motionProgram, this->motionArgs);
                this->process->waitForStarted(-1);
            }
            this->cameraStateMachine = RUNNING_MOTION;
            break;
        case STOP_MOTION:
            this->tbxStatus->append("--Stopping Motion Detection");
            this->process->close();
            this->process->waitForFinished();
            delete this->process;

            // Start the monitor only process
            this->tbxStatus->append("--Starting Monitor");
            this->process = new QProcess();

            while(this->process->state() != QProcess::Running)
            {
                this->process->start(this->motionProgram, this->monitorOnlyArgs);
                this->process->waitForStarted(-1);
            }
            this->cameraStateMachine = MONITOR_ONLY;
            break;
        case RUNNING_MOTION:
            if(this->process->state() != QProcess::Running || this->process->pid() == 0)
            {
                this->tbxStatus->append("Camera Crashed, restarting last state (RUNNING_MOTION)");
                this->cameraStateMachine = START_MOTION;
            }
            else
                sleep(1);
            break;
        case MONITOR_ONLY:
            cout << this->process->pid() << endl;
            if(this->process->state() != QProcess::Running || this->process->pid() == 0)
            {
                this->tbxStatus->append("Camera Crashed, restarting last state (MONITOR_ONLY)");
                this->cameraStateMachine = STOP_MOTION;
            }
            else
                sleep(1);
            break;
        case QUIT:
            return;
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

//
// Stop all monitoring and get ready to quit the thread
//
void CameraThreadClass::stopAll()
{
    this->cameraStateMachine = QUIT;
}
