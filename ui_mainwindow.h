/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Nov 13 01:46:24 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *m_sendEdit;
    QLabel *Label_gravity;
    QLabel *label;
    QLabel *Label_roll;
    QLabel *label_2;
    QLabel *Label_pitch;
    QLabel *label_3;
    QLabel *Label_yaw;
    QLabel *label_4;
    QPushButton *m_connectButton;
    QPushButton *m_disconnectButton;
    QPushButton *m_sendButton;
    QCheckBox *m_enableLoggingCb;
    QLineEdit *m_logFileLe;
    QPushButton *m_logFileFileDialog;
    QTextBrowser *m_receiveEdit;
    QLabel *m_label_debug;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        m_sendEdit = new QTextEdit(centralwidget);
        m_sendEdit->setObjectName(QString::fromUtf8("m_sendEdit"));
        m_sendEdit->setGeometry(QRect(30, 190, 251, 101));
        Label_gravity = new QLabel(centralwidget);
        Label_gravity->setObjectName(QString::fromUtf8("Label_gravity"));
        Label_gravity->setGeometry(QRect(70, 330, 101, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 340, 69, 17));
        Label_roll = new QLabel(centralwidget);
        Label_roll->setObjectName(QString::fromUtf8("Label_roll"));
        Label_roll->setGeometry(QRect(350, 70, 101, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(480, 80, 69, 17));
        Label_pitch = new QLabel(centralwidget);
        Label_pitch->setObjectName(QString::fromUtf8("Label_pitch"));
        Label_pitch->setGeometry(QRect(350, 130, 101, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(500, 140, 69, 17));
        Label_yaw = new QLabel(centralwidget);
        Label_yaw->setObjectName(QString::fromUtf8("Label_yaw"));
        Label_yaw->setGeometry(QRect(350, 190, 101, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(500, 200, 69, 17));
        m_connectButton = new QPushButton(centralwidget);
        m_connectButton->setObjectName(QString::fromUtf8("m_connectButton"));
        m_connectButton->setGeometry(QRect(70, 380, 101, 27));
        m_disconnectButton = new QPushButton(centralwidget);
        m_disconnectButton->setObjectName(QString::fromUtf8("m_disconnectButton"));
        m_disconnectButton->setGeometry(QRect(190, 380, 101, 27));
        m_sendButton = new QPushButton(centralwidget);
        m_sendButton->setObjectName(QString::fromUtf8("m_sendButton"));
        m_sendButton->setGeometry(QRect(120, 430, 101, 27));
        m_enableLoggingCb = new QCheckBox(centralwidget);
        m_enableLoggingCb->setObjectName(QString::fromUtf8("m_enableLoggingCb"));
        m_enableLoggingCb->setGeometry(QRect(360, 390, 61, 21));
        m_logFileLe = new QLineEdit(centralwidget);
        m_logFileLe->setObjectName(QString::fromUtf8("m_logFileLe"));
        m_logFileLe->setGeometry(QRect(430, 390, 151, 31));
        m_logFileFileDialog = new QPushButton(centralwidget);
        m_logFileFileDialog->setObjectName(QString::fromUtf8("m_logFileFileDialog"));
        m_logFileFileDialog->setGeometry(QRect(610, 390, 101, 27));
        m_receiveEdit = new QTextBrowser(centralwidget);
        m_receiveEdit->setObjectName(QString::fromUtf8("m_receiveEdit"));
        m_receiveEdit->setGeometry(QRect(30, 30, 251, 151));
        m_label_debug = new QLabel(centralwidget);
        m_label_debug->setObjectName(QString::fromUtf8("m_label_debug"));
        m_label_debug->setGeometry(QRect(650, 10, 69, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        Label_gravity->setText(QString());
        label->setText(QApplication::translate("MainWindow", "gravity", 0, QApplication::UnicodeUTF8));
        Label_roll->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "roll", 0, QApplication::UnicodeUTF8));
        Label_pitch->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "pitch", 0, QApplication::UnicodeUTF8));
        Label_yaw->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "yaw", 0, QApplication::UnicodeUTF8));
        m_connectButton->setText(QApplication::translate("MainWindow", "connect", 0, QApplication::UnicodeUTF8));
        m_disconnectButton->setText(QApplication::translate("MainWindow", "disconnect", 0, QApplication::UnicodeUTF8));
        m_sendButton->setText(QApplication::translate("MainWindow", "send", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        m_enableLoggingCb->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        m_enableLoggingCb->setText(QApplication::translate("MainWindow", "log", 0, QApplication::UnicodeUTF8));
        m_logFileFileDialog->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        m_label_debug->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
