#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Start Camera Thread
    this->cameraThread = new CameraThreadClass();
    this->cameraThread->start();

    // Create Timer object
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimerEvent()));

    // Set the image path
    this->currentImagePath = "/home/pi/Desktop/CamPictures/motion/currentImage.jpg";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_2_triggered()
{
    cout << "\nClosing App" << endl;
    this->cameraThread->exit();
    this->close();
}

void MainWindow::on_actionStart_System_triggered()
{
    if(ui->actionStart_System->text() == "Start System")
    {
        this->cameraThread->setRunning(true);
        ui->actionStart_System->setText("Stop System");
        this->timer->start(1000);

    }
    else
    {
        this->cameraThread->setRunning(false);
        ui->actionStart_System->setText("Start System");
        this->timer->stop();
    }
}

void MainWindow::onTimerEvent()
{
    //cout << "Repainting image" << endl;
    this->currentImage.load(this->currentImagePath);
    ui->lblCurrentImage->setPixmap(this->currentImage);
}

