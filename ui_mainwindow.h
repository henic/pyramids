/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jan 13 08:25:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_game;
    QAction *actionSave_game;
    QAction *actionLoad_game;
    QAction *actionSave_options;
    QAction *actionLoad_options;
    QAction *actionNew_Game;
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionQuit;
    QAction *actionOptions;
    QAction *actionTakeback;
    QAction *actionAbout;
    QAction *actionAuthor;
    QAction *actionMove_now;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *Layout_buttons;
    QHBoxLayout *horizontalLayout_buttons;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Stop;
    QSpacerItem *horizontalSpacer_1;
    QPushButton *pushButton_Takeback;
    QPushButton *pushButton_Move_Now;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Options;
    QPushButton *pushButton_Quit;
    QLabel *Status;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_estimating_now;
    QLabel *label_best_estimated;
    QLabel *label_expected_rest_time;
    QLabel *label_rest_time;
    QGroupBox *groupBox_player_0;
    QLabel *label_player_name_0;
    QLabel *label_chips_number_0;
    QGroupBox *groupBox_player_1;
    QLabel *label_player_name_1;
    QLabel *label_chips_number_1;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(749, 564);
        actionNew_game = new QAction(MainWindow);
        actionNew_game->setObjectName(QString::fromUtf8("actionNew_game"));
        actionSave_game = new QAction(MainWindow);
        actionSave_game->setObjectName(QString::fromUtf8("actionSave_game"));
        actionLoad_game = new QAction(MainWindow);
        actionLoad_game->setObjectName(QString::fromUtf8("actionLoad_game"));
        actionSave_options = new QAction(MainWindow);
        actionSave_options->setObjectName(QString::fromUtf8("actionSave_options"));
        actionLoad_options = new QAction(MainWindow);
        actionLoad_options->setObjectName(QString::fromUtf8("actionLoad_options"));
        actionNew_Game = new QAction(MainWindow);
        actionNew_Game->setObjectName(QString::fromUtf8("actionNew_Game"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionTakeback = new QAction(MainWindow);
        actionTakeback->setObjectName(QString::fromUtf8("actionTakeback"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAuthor = new QAction(MainWindow);
        actionAuthor->setObjectName(QString::fromUtf8("actionAuthor"));
        actionMove_now = new QAction(MainWindow);
        actionMove_now->setObjectName(QString::fromUtf8("actionMove_now"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(9, 480, 731, 31));
        Layout_buttons = new QVBoxLayout(verticalLayoutWidget_2);
        Layout_buttons->setSpacing(6);
        Layout_buttons->setContentsMargins(11, 11, 11, 11);
        Layout_buttons->setObjectName(QString::fromUtf8("Layout_buttons"));
        Layout_buttons->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_buttons = new QHBoxLayout();
        horizontalLayout_buttons->setSpacing(6);
        horizontalLayout_buttons->setObjectName(QString::fromUtf8("horizontalLayout_buttons"));
        pushButton_Start = new QPushButton(verticalLayoutWidget_2);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));

        horizontalLayout_buttons->addWidget(pushButton_Start);

        pushButton_Stop = new QPushButton(verticalLayoutWidget_2);
        pushButton_Stop->setObjectName(QString::fromUtf8("pushButton_Stop"));
        pushButton_Stop->setEnabled(false);

        horizontalLayout_buttons->addWidget(pushButton_Stop);

        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_buttons->addItem(horizontalSpacer_1);

        pushButton_Takeback = new QPushButton(verticalLayoutWidget_2);
        pushButton_Takeback->setObjectName(QString::fromUtf8("pushButton_Takeback"));
        pushButton_Takeback->setEnabled(false);

        horizontalLayout_buttons->addWidget(pushButton_Takeback);

        pushButton_Move_Now = new QPushButton(verticalLayoutWidget_2);
        pushButton_Move_Now->setObjectName(QString::fromUtf8("pushButton_Move_Now"));
        pushButton_Move_Now->setEnabled(false);

        horizontalLayout_buttons->addWidget(pushButton_Move_Now);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_buttons->addItem(horizontalSpacer_2);

        pushButton_Options = new QPushButton(verticalLayoutWidget_2);
        pushButton_Options->setObjectName(QString::fromUtf8("pushButton_Options"));

        horizontalLayout_buttons->addWidget(pushButton_Options);

        pushButton_Quit = new QPushButton(verticalLayoutWidget_2);
        pushButton_Quit->setObjectName(QString::fromUtf8("pushButton_Quit"));

        horizontalLayout_buttons->addWidget(pushButton_Quit);


        Layout_buttons->addLayout(horizontalLayout_buttons);

        Status = new QLabel(centralWidget);
        Status->setObjectName(QString::fromUtf8("Status"));
        Status->setGeometry(QRect(10, 455, 729, 18));
        Status->setMinimumSize(QSize(0, 18));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 430, 731, 21));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_estimating_now = new QLabel(layoutWidget);
        label_estimating_now->setObjectName(QString::fromUtf8("label_estimating_now"));
        label_estimating_now->setMinimumSize(QSize(0, 14));

        horizontalLayout_3->addWidget(label_estimating_now);

        label_best_estimated = new QLabel(layoutWidget);
        label_best_estimated->setObjectName(QString::fromUtf8("label_best_estimated"));

        horizontalLayout_3->addWidget(label_best_estimated);

        label_expected_rest_time = new QLabel(layoutWidget);
        label_expected_rest_time->setObjectName(QString::fromUtf8("label_expected_rest_time"));

        horizontalLayout_3->addWidget(label_expected_rest_time);

        label_rest_time = new QLabel(layoutWidget);
        label_rest_time->setObjectName(QString::fromUtf8("label_rest_time"));

        horizontalLayout_3->addWidget(label_rest_time);

        groupBox_player_0 = new QGroupBox(centralWidget);
        groupBox_player_0->setObjectName(QString::fromUtf8("groupBox_player_0"));
        groupBox_player_0->setGeometry(QRect(10, 0, 141, 421));
        label_player_name_0 = new QLabel(groupBox_player_0);
        label_player_name_0->setObjectName(QString::fromUtf8("label_player_name_0"));
        label_player_name_0->setGeometry(QRect(40, 30, 46, 13));
        label_player_name_0->setAlignment(Qt::AlignCenter);
        label_chips_number_0 = new QLabel(groupBox_player_0);
        label_chips_number_0->setObjectName(QString::fromUtf8("label_chips_number_0"));
        label_chips_number_0->setGeometry(QRect(40, 70, 51, 16));
        label_chips_number_0->setAlignment(Qt::AlignCenter);
        groupBox_player_1 = new QGroupBox(centralWidget);
        groupBox_player_1->setObjectName(QString::fromUtf8("groupBox_player_1"));
        groupBox_player_1->setGeometry(QRect(600, 0, 141, 421));
        label_player_name_1 = new QLabel(groupBox_player_1);
        label_player_name_1->setObjectName(QString::fromUtf8("label_player_name_1"));
        label_player_name_1->setGeometry(QRect(40, 30, 46, 13));
        label_player_name_1->setAlignment(Qt::AlignCenter);
        label_chips_number_1 = new QLabel(groupBox_player_1);
        label_chips_number_1->setObjectName(QString::fromUtf8("label_chips_number_1"));
        label_chips_number_1->setGeometry(QRect(40, 70, 51, 16));
        label_chips_number_1->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 749, 18));
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
        actionNew_game->setText(QApplication::translate("MainWindow", "New game", 0, QApplication::UnicodeUTF8));
        actionSave_game->setText(QApplication::translate("MainWindow", "Save game", 0, QApplication::UnicodeUTF8));
        actionLoad_game->setText(QApplication::translate("MainWindow", "Load game", 0, QApplication::UnicodeUTF8));
        actionSave_options->setText(QApplication::translate("MainWindow", "Save options", 0, QApplication::UnicodeUTF8));
        actionLoad_options->setText(QApplication::translate("MainWindow", "Load options", 0, QApplication::UnicodeUTF8));
        actionNew_Game->setText(QApplication::translate("MainWindow", "New game", 0, QApplication::UnicodeUTF8));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        actionTakeback->setText(QApplication::translate("MainWindow", "Takeback", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About ", 0, QApplication::UnicodeUTF8));
        actionAuthor->setText(QApplication::translate("MainWindow", "Author", 0, QApplication::UnicodeUTF8));
        actionMove_now->setText(QApplication::translate("MainWindow", "Move now", 0, QApplication::UnicodeUTF8));
        pushButton_Start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButton_Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        pushButton_Takeback->setText(QApplication::translate("MainWindow", "Takeback", 0, QApplication::UnicodeUTF8));
        pushButton_Move_Now->setText(QApplication::translate("MainWindow", "Move now", 0, QApplication::UnicodeUTF8));
        pushButton_Options->setText(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        pushButton_Quit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        Status->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        label_estimating_now->setText(QApplication::translate("MainWindow", "Estimating now: B1", 0, QApplication::UnicodeUTF8));
        label_best_estimated->setText(QApplication::translate("MainWindow", "Best estimated:", 0, QApplication::UnicodeUTF8));
        label_expected_rest_time->setText(QApplication::translate("MainWindow", "Expected rest time:", 0, QApplication::UnicodeUTF8));
        label_rest_time->setText(QApplication::translate("MainWindow", "Rest time:", 0, QApplication::UnicodeUTF8));
        groupBox_player_0->setTitle(QApplication::translate("MainWindow", "Player 0", 0, QApplication::UnicodeUTF8));
        label_player_name_0->setText(QApplication::translate("MainWindow", "Vasya", 0, QApplication::UnicodeUTF8));
        label_chips_number_0->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox_player_1->setTitle(QApplication::translate("MainWindow", "Player 1", 0, QApplication::UnicodeUTF8));
        label_player_name_1->setText(QApplication::translate("MainWindow", "Petya", 0, QApplication::UnicodeUTF8));
        label_chips_number_1->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
