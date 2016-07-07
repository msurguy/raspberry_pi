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

    // Attributes
    Ui::MainWindow *ui;
    SettingsClass Settings;
    QTimer *imageTimer;
    QPixmap currentImage;
    ColorStateMachineType colorState;


    // Methods
    void startFsWebcam();
    void readConfigFile();
};

#endif // MAINWINDOW_H
