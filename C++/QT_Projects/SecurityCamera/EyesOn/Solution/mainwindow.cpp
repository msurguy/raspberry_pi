#include "mainwindow.h"
#include "ui_mainwindow.h"

//
// Main Window Constructor
//
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Read the config file
#ifdef QT_DEBUG
    Settings.configFilePath = "/home/pi/Desktop/github/raspberry_pi/C++/QT_Projects/SecurityCamera/EyesOn/Release/settings.cfg";
#else
    Settings.configFilePath = "settings.cfg";
#endif
    this->readConfigFile();
    ui->lblCurrentImage->resize(Settings.resolutionWidth, Settings.resolutionHeight);

    // Start Camera Thread
    this->cameraThread = new CameraThreadClass();
    this->cameraThread->start();

    // Create Timer object
    this->imageTimer = new QTimer(this);
    connect(this->imageTimer, SIGNAL(timeout()), this, SLOT(onImageTimerEvent()));

    // Start the Current Image Timer
    this->imageTimer->start(1000);

} // Constructor

//
// Main Window Destructor
//
MainWindow::~MainWindow()
{
    cout << "Exiting program" << endl;
    this->cameraThread->stopAll();

    this->cameraThread->quit();
    delete this->cameraThread;
    delete ui;
} // Destructor

/////////////////////////////////////////////////////////////////////////////////////////
//
// Action Slots
//
/////////////////////////////////////////////////////////////////////////////////////////


//
// Start/Stop Action
//

void MainWindow::on_btnStartSystem_clicked()
{

    if(ui->btnStartSystem->text() == "Start System")
    {
        this->cameraThread->setRunning(true);
        ui->btnStartSystem->setText("Stop System");
        ui->lblCurrentImageText->setStyleSheet("QLabel { background-color : red; color : black; }");
        ui->lblCurrentImageText->setText("Motion Sensor On");
    }
    else
    {
        this->cameraThread->setRunning(false);
        ui->btnStartSystem->setText("Start System");
        ui->lblCurrentImageText->setStyleSheet("QLabel { background-color : green; color : black; }");
        ui->lblCurrentImageText->setText("Monitor Only");
    }
}

//
// Timer to load the latest image
//
void MainWindow::onImageTimerEvent()
{
    this->currentImage.load(Settings.currentImagePath);
    ui->lblCurrentImage->setPixmap(this->currentImage.scaled(Settings.resolutionWidth, Settings.resolutionHeight, Qt::KeepAspectRatio));
} // Image Event Timer

//
// Read the Config file for the settings
//
void MainWindow::readConfigFile()
{
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

