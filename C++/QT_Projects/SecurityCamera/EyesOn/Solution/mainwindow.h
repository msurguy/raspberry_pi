#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <iostream>

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
    void on_actionExit_2_triggered();
    void on_actionStart_System_triggered();
    void onImageTimerEvent();

private:
    Ui::MainWindow *ui;
    CameraThreadClass *cameraThread;
    QTimer *imageTimer;
    QString currentImagePath;
    QPixmap currentImage;


};

#endif // MAINWINDOW_H
