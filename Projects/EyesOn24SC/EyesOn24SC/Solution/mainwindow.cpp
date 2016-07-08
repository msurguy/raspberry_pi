#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // There is a bug with Motion, you need to run FSWebCam first to set the device properly
    this->startFsWebcam();

    // Read the config file
    this->readConfigFile();

    // Configure motion program
    this->configureMotion();

    // Create Timer object
    this->imageTimer = new QTimer(this);
    connect(this->imageTimer, SIGNAL(timeout()), this, SLOT(onImageTimerEvent()));

    // Start the Current Image Timer
    this->imageTimer->start(1000 / Settings.frameRate);

    this->colorState = ORANGE;
}

MainWindow::~MainWindow()
{
    if(this->monitorProcess->pid() != 0 && this->monitorProcess->state() == QProcess::Running)
    {
        cout << "Terminating Monitor Process" << endl;
        this->monitorProcess->kill();
        this->monitorProcess->waitForFinished();
    }
    if(this->motionProcess->pid() != 0 && this->motionProcess->state() == QProcess::Running)
    {
        cout << "Terminating Motion Detection Process" << endl;
        this->motionProcess->kill();
        this->motionProcess->waitForFinished();
    }
    delete this->monitorProcess;
    delete this->motionProcess;
    delete this->imageTimer;
    delete ui;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
// Action Slots
//
/////////////////////////////////////////////////////////////////////////////////////////

//
// Start button clicked Slot
//
void MainWindow::on_btnStartSystem_clicked()
{
    if(ui->btnStartSystem->text() == "Start System")
    {
        //this->cameraThread->setRunning(true);
        ui->btnStartSystem->setText("Stop System");
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : green; color : black; }");
        ui->lblCurrentStatus->setText("Motion Sensor On");
        this->cameraState = STOP_MONITOR;
    }
    else
    {
        //this->cameraThread->setRunning(false);
        ui->btnStartSystem->setText("Start System");
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : orange; color : black; }");
        ui->lblCurrentStatus->setText("Monitor Only");
        this->cameraState = STOP_MOTION;
    }
} // btnClicked()

//
// Timer to load the latest image
//
void MainWindow::onImageTimerEvent()
{
    this->currentImage.load(Settings.currentImagePath);
    if(!this->currentImage.isNull())
    {
        ui->lblCurrentImage->setPixmap(this->currentImage.scaled(Settings.resolutionWidth, Settings.resolutionHeight, Qt::KeepAspectRatio));
    }

    switch(this->cameraState)
    {
    case START_MONITOR:
        ui->tbxStatus->appendPlainText("Starting Monitor Only");
        this->monitorProcess->start(this->motionProgram, this->monitorOnlyArgs);
        this->monitorProcess->waitForStarted();
        this->colorState = ORANGE;
        this->cameraState = RUNNING_MONITOR;
        break;
    case RUNNING_MONITOR:
        //cout << "Monitor Process ID: " << this->monitorProcess->pid() << endl;
        if(this->monitorProcess->state() != QProcess::Running || this->monitorProcess->pid() == 0)
        {
            cout << "Camera Crashed! Restarting last state (RUNNING_MONITOR)" << endl;
            ui->tbxStatus->appendPlainText("Camera Crashed! Restarting last state (RUNNING_MONITOR)");
            this->monitorProcess->kill();
            this->monitorProcess->waitForFinished();
            this->cameraState = START_MONITOR;
        }
        break;
    case STOP_MONITOR:
        ui->tbxStatus->appendPlainText("Stopping Monitor Only");
        this->monitorProcess->kill();
        this->monitorProcess->waitForFinished();
        this->cameraState = START_MOTION;
        break;
    case START_MOTION:
        ui->tbxStatus->appendPlainText("Starting Motion Detection");
        this->motionProcess->start(this->motionProgram, this->motionArgs);
        this->motionProcess->waitForStarted();
        this->colorState = GREEN;
        this->cameraState = RUNNING_MOTION;
        break;
    case RUNNING_MOTION:
        //cout << "Motion ProcessID : " << this->motionProcess->pid() << endl;
        if(this->motionProcess->state() != QProcess::Running || this->motionProcess->pid() == 0)
        {
            cout << "Camera Crashed! Restarting last state (RUNNING_MOTION)" << endl;
            ui->tbxStatus->appendPlainText("Camera Crashed! Restarting last state (RUNNING_MOTION)");
            this->motionProcess->kill();
            this->motionProcess->waitForFinished();
            this->cameraState = START_MOTION;
        }
        break;
    case STOP_MOTION:
        ui->tbxStatus->appendPlainText("Stopping Motion Detection");
        this->motionProcess->kill();
        this->motionProcess->waitForFinished();
        this->cameraState = START_MONITOR;
        break;
    }

    switch(this->colorState)
    {
    case RED:
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : green; color : black; }");
        this->colorState = GREEN;
        break;
    case GREEN:
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : red; color : black; }");
        this->colorState = RED;
        break;
    case ORANGE:
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : orange; color : black; }");
        break;
    }
} // Image Event Timer

/////////////////////////////////////////////////////////////////////////////////////////
//
// Methods
//
/////////////////////////////////////////////////////////////////////////////////////////

//
// Start FSWebcam
//
void MainWindow::startFsWebcam()
{
    QProcess *process = new QProcess();
    QString program = "fswebcam";
    QStringList args;
    args << "-r" << "1280x720" << "--device" << "/dev/video0";
    process->start(program, args);
    process->waitForFinished(-1);
    delete process;
} // startFsWebcam()

//
// Configure the Motion program vars
//
void MainWindow::configureMotion()
{
    this->cameraState = START_MONITOR;
    this->motionProgram = "motion";

    // Monitor only vars
    this->monitorProcess = new QProcess();
    this->monitorOnlyArgs << "-c" << Settings.monitorOnlyConfPath;

    // Motion and monitor vars
    this->motionProcess = new QProcess();
    this->motionArgs << "-c" << Settings.motionConfPath;
} // configureMotion()

//
// Read the Config file for the settings
//
void MainWindow::readConfigFile()
{
#ifdef QT_DEBUG
    Settings.configFilePath = "/home/pi/Desktop/github/raspberry_pi/Projects/EyesOn24SC/EyesOn24SC/Release/settings.cfg";
#else
    Settings.configFilePath = QDir::currentPath() + "/settings.cfg";
#endif

    QFile settingsFile(Settings.configFilePath);

    if(settingsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream ts(&settingsFile);
        while(!ts.atEnd())
        {
            QString line = ts.readLine();
            QStringList words = line.split(" ");

            if(words[0] == "Resolution_Width:")
            {
                Settings.resolutionWidth = words[1].toInt();
            }
            else if(words[0] == "Resolution_Height:")
            {
                Settings.resolutionHeight = words[1].toInt();
            }
            else if(words[0] == "Frame_Rate:")
            {
                Settings.frameRate = words[1].toInt();
            }
            else if(words[0] == "Monitor_Only_Cfg_File_Path:")
            {
                Settings.monitorOnlyConfPath = words[1];
            }
            else if(words[0] == "Motion_Cfg_File_Path:")
            {
                Settings.motionConfPath = words[1];
            }
            else if(words[0] == "Current_Image_Path:")
            {
                Settings.currentImagePath = words[1];
            }
        } // while not EOF
    }
    else
    {
    }
} // readConfigFile()
