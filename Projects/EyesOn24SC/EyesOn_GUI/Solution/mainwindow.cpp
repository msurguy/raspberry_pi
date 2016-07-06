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

    // There is a bug with Motion, you need to run FSWebCam first to set the device properly
    QProcess *process = new QProcess();
    QString program = "fswebcam";
    QStringList args;
    args << "-r" << "640x480" << "--device" << "/dev/video0";
    process->start(program, args);
    process->waitForFinished(-1);
    delete process;

    // Read the config file
#ifdef QT_DEBUG
    Settings.configFilePath = "/home/pi/Desktop/github/raspberry_pi/Projects/EyesOn24SC/EyesOn_GUI/Release/settings.cfg";
#else
    Settings.configFilePath = QDir::currentPath() + "/settings.cfg";
#endif
    this->readConfigFile();
    this->currentImage.size() = (QSize(Settings.resolutionWidth, Settings.resolutionHeight));
    ui->lblCurrentImage->resize(Settings.resolutionWidth, Settings.resolutionHeight);

    // Start Camera Thread
    this->cameraThread = new CameraThreadClass(this, Settings, ui->tbxStatus);
    this->cameraThread->start();

    // Create Timer object
    this->imageTimer = new QTimer(this);
    connect(this->imageTimer, SIGNAL(timeout()), this, SLOT(onImageTimerEvent()));

    // Start the Current Image Timer
    this->imageTimer->start(250);

    this->colorStateMachine = ORANGE;

#ifdef NO_NOT_COMPILE
    // Use webcam IP address for picture
    QUrl page;
    QWebView *m_view = new QWebView(this);
    connect(m_view, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
    page.setScheme("http");
    page.setHost("127.0.0.1");
    page.setPort(8081);
    m_view->load(page);
    m_view->show();
    QWebElement element = m_view->page()->mainFrame()->documentElement();
    element = element.findFirst("img");
    QPainter painter(&this->currentImage);
    element.render(&painter);
    this->currentImage.save("/home/pi/Desktop/github/raspberry_pi/Projects/EyesOn24SC/EyesOn_GUI/Release/picture.jpg");
    ui->lblCurrentImage->setPixmap(this->currentImage);
#endif
} // Constructor

//
// Main Window Destructor
//
MainWindow::~MainWindow()
{
    ui->tbxStatus->append("-----Exiting System-----");
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
        this->colorStateMachine = RED;
    }
    else
    {
        this->cameraThread->setRunning(false);
        ui->btnStartSystem->setText("Start System");
        ui->lblCurrentImageText->setStyleSheet("QLabel { background-color : orange; color : black; }");
        ui->lblCurrentImageText->setText("Monitor Only");
        this->colorStateMachine = ORANGE;
    }
}

//
// Timer to load the latest image
//
void MainWindow::onImageTimerEvent()
{
#ifndef USE_JPG
    this->currentImage.load(Settings.currentImagePath);
    ui->lblCurrentImage->setPixmap(this->currentImage.scaled(Settings.resolutionWidth, Settings.resolutionHeight, Qt::KeepAspectRatio));
#else
    ui->lblCurrentImage->setPixmap(this->currentImage);
#endif

    switch(this->colorStateMachine)
    {
    case RED:
        ui->lblCurrentImageText->setStyleSheet("QLabel { background-color : green; color : black; }");
        this->colorStateMachine = GREEN;
        break;
    case GREEN:
        ui->lblCurrentImageText->setStyleSheet("QLabel { background-color : red; color : black; }");
        this->colorStateMachine = RED;
        break;
    default:
        ui->lblCurrentImageText->setStyleSheet("QLabel { background-color : orange; color : black; }");
        this->colorStateMachine = ORANGE;
        break;
    }
} // Image Event Timer


//
// Web Cam IP finished loading
//
#ifdef NO_NOT_COMPILE
void MainWindow::onLoadFinished(bool var)
{

    ui->lblCurrentImage->setPixmap(this->currentImage);
} // Web Cam image load
#endif

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


void MainWindow::on_tbxStatus_textChanged()
{
    QTextCursor cursor = ui->tbxStatus->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->tbxStatus->setTextCursor(cursor);
}
