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

    // Create Timer object
    this->imageTimer = new QTimer(this);
    connect(this->imageTimer, SIGNAL(timeout()), this, SLOT(onImageTimerEvent()));

    // Start the Current Image Timer
    this->imageTimer->start(1000);

    this->colorState = ORANGE;
}

MainWindow::~MainWindow()
{
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
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : red; color : black; }");
        ui->lblCurrentStatus->setText("Motion Sensor On");
        this->colorState = RED;
    }
    else
    {
        //this->cameraThread->setRunning(false);
        ui->btnStartSystem->setText("Start System");
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : orange; color : black; }");
        ui->lblCurrentStatus->setText("Monitor Only");
        this->colorState = ORANGE;
    }
} // btnClicked()

//
// Timer to load the latest image
//
void MainWindow::onImageTimerEvent()
{
    this->currentImage.load(Settings.currentImagePath);
    ui->lblCurrentImage->setPixmap(this->currentImage.scaled(Settings.resolutionWidth, Settings.resolutionHeight, Qt::KeepAspectRatio));

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
    default:
        ui->lblCurrentStatus->setStyleSheet("QLabel { background-color : orange; color : black; }");
        this->colorState = ORANGE;
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
    args << "-r" << "640x480" << "--device" << "/dev/video0";
    process->start(program, args);
    process->waitForFinished(-1);
    delete process;
} // startFsWebcam()


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
