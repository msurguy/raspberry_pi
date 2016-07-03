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

    // Start Camera Thread
    this->cameraThread = new CameraThreadClass();
    this->cameraThread->start();

    // Create Timer object
    this->imageTimer = new QTimer(this);
    connect(this->imageTimer, SIGNAL(timeout()), this, SLOT(onImageTimerEvent()));

    // Set the image path
    this->currentImagePath = "/home/pi/Desktop/CamPictures/motion/currentImage.jpg";
    this->imageTimer->start(1000);
} // Constructor

//
// Main Window Destructor
MainWindow::~MainWindow()
{
    cout << "Exiting program" << endl;
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
// Exit action
//
void MainWindow::on_actionExit_2_triggered()
{
    delete this;
} // actionExit()

//
// Start/Stop Action
//
void MainWindow::on_actionStart_System_triggered()
{
    if(ui->actionStart_System->text() == "Start System")
    {
        this->cameraThread->setRunning(true);
        ui->actionStart_System->setText("Stop System");
    }
    else
    {
        this->cameraThread->setRunning(false);
        ui->actionStart_System->setText("Start System");
    }
} // actionStartStop()

//
// Timer to load the latest image
//
void MainWindow::onImageTimerEvent()
{
    this->currentImage.load(this->currentImagePath);
    ui->lblCurrentImage->setPixmap(this->currentImage);
} // Image Event Timer

