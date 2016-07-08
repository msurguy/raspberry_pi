#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <iostream>
using namespace std;

#include "SettingsClass.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnStartSystem_clicked();
    void onImageTimerEvent();

private:
    enum ColorStateMachineType
    {
        ORANGE = 0,
        RED = 1,
        GREEN = 2
    };
    enum CameraStateMachineType
    {
        START_MONITOR,
        RUNNING_MONITOR,
        STOP_MONITOR,
        START_MOTION,
        RUNNING_MOTION,
        STOP_MOTION
    };

    // Attributes
    Ui::MainWindow *ui;
    SettingsClass Settings;
    QTimer *imageTimer;
    QPixmap currentImage;
    ColorStateMachineType colorState;

    // Camera Vars
    CameraStateMachineType cameraState;

    // Motion program vars
    QString motionProgram;

    // Motion program variables for monitor only
    QProcess *monitorProcess;
    QString monitorOnlyConfPath;
    QStringList monitorOnlyArgs;

    // Motion program variables for motion and monitor
    QProcess *motionProcess;
    QString motionConfPath;
    QStringList motionArgs;

    // Methods
    void startFsWebcam();
    void readConfigFile();
    void configureMotion();
};

#endif // MAINWINDOW_H
