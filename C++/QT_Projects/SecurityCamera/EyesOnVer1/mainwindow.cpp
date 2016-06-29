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

    }
    else
    {
        this->cameraThread->setRunning(false);
        ui->actionStart_System->setText("Start System");
    }
}
