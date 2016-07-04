/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblCurrentImage;
    QLabel *lblCurrentImageText;
    QPushButton *btnStartSystem;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(880, 530);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(true);
        lblCurrentImage = new QLabel(centralWidget);
        lblCurrentImage->setObjectName(QString::fromUtf8("lblCurrentImage"));
        lblCurrentImage->setGeometry(QRect(10, 40, 640, 480));
        lblCurrentImage->setFrameShape(QFrame::WinPanel);
        lblCurrentImage->setFrameShadow(QFrame::Sunken);
        lblCurrentImage->setLineWidth(3);
        lblCurrentImage->setScaledContents(true);
        lblCurrentImageText = new QLabel(centralWidget);
        lblCurrentImageText->setObjectName(QString::fromUtf8("lblCurrentImageText"));
        lblCurrentImageText->setGeometry(QRect(10, 10, 640, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        lblCurrentImageText->setFont(font);
        lblCurrentImageText->setAutoFillBackground(false);
        lblCurrentImageText->setStyleSheet(QString::fromUtf8("background-color: green;\n"
"color: rgb(0, 0, 0);"));
        lblCurrentImageText->setFrameShape(QFrame::WinPanel);
        lblCurrentImageText->setAlignment(Qt::AlignCenter);
        lblCurrentImageText->setTextInteractionFlags(Qt::NoTextInteraction);
        btnStartSystem = new QPushButton(centralWidget);
        btnStartSystem->setObjectName(QString::fromUtf8("btnStartSystem"));
        btnStartSystem->setGeometry(QRect(660, 10, 211, 51));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Eyes On Security System", 0, QApplication::UnicodeUTF8));
        lblCurrentImage->setText(QString());
        lblCurrentImageText->setText(QApplication::translate("MainWindow", "Monitor Only", 0, QApplication::UnicodeUTF8));
        btnStartSystem->setText(QApplication::translate("MainWindow", "Start System", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
