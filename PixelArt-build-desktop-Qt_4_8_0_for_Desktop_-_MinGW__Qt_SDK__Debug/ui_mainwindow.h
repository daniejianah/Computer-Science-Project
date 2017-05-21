/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun May 21 23:27:25 2017
**      by: Qt User Interface Compiler version 4.8.0
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
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_image;
    QPushButton *btn_image;
    QLabel *FilePathLabel;
    QPushButton *Pixelize;
    QPushButton *PixArt;
    QPushButton *SaveImg;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(933, 661);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_image = new QLabel(centralWidget);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setGeometry(QRect(20, 0, 571, 421));
        btn_image = new QPushButton(centralWidget);
        btn_image->setObjectName(QString::fromUtf8("btn_image"));
        btn_image->setGeometry(QRect(640, 30, 131, 41));
        FilePathLabel = new QLabel(centralWidget);
        FilePathLabel->setObjectName(QString::fromUtf8("FilePathLabel"));
        FilePathLabel->setGeometry(QRect(60, 590, 281, 16));
        Pixelize = new QPushButton(centralWidget);
        Pixelize->setObjectName(QString::fromUtf8("Pixelize"));
        Pixelize->setGeometry(QRect(640, 90, 131, 51));
        PixArt = new QPushButton(centralWidget);
        PixArt->setObjectName(QString::fromUtf8("PixArt"));
        PixArt->setGeometry(QRect(640, 160, 131, 51));
        SaveImg = new QPushButton(centralWidget);
        SaveImg->setObjectName(QString::fromUtf8("SaveImg"));
        SaveImg->setGeometry(QRect(640, 230, 131, 51));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 933, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_image->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        btn_image->setText(QApplication::translate("MainWindow", "Choose an image ", 0, QApplication::UnicodeUTF8));
        FilePathLabel->setText(QApplication::translate("MainWindow", "FilePathLabel", 0, QApplication::UnicodeUTF8));
        Pixelize->setText(QApplication::translate("MainWindow", "Pixelize", 0, QApplication::UnicodeUTF8));
        PixArt->setText(QApplication::translate("MainWindow", "PixArt", 0, QApplication::UnicodeUTF8));
        SaveImg->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
