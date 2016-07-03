#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <iostream>

#include "SettingsClass.h"
#include "CameraThreadClass.h"

using namespace std;

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
    Ui::MainWindow *ui;
    SettingsClass Settings;
    CameraThreadClass *cameraThread;
    QTimer *imageTimer;
    QPixmap currentImage;

    void readConfigFile();

};

#endif // MAINWINDOW_H
