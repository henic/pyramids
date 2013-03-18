/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created: Sun Jan 13 08:25:04 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QCheckBox *checkBox_Skip_Confirmation;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancel;
    QGroupBox *groupBox_Game_Config;
    QLineEdit *lineEdit_board_size;
    QLabel *label_board_size;
    QLabel *label_required_length;
    QLineEdit *lineEdit_required_length;
    QLineEdit *lineEdit_chips_number;
    QLabel *label_chips_number;
    QGroupBox *groupBox_players_Level;
    QLabel *label_comp0_level_2;
    QSlider *horizontalSlider_options_comp0_level;
    QLabel *label_comp1_level_2;
    QLineEdit *lineEdit_show_threat_sec;
    QLabel *label_comp0_level;
    QLabel *label_5;
    QCheckBox *checkBox_0_is_comp;
    QCheckBox *checkBox_Limit_Move_Time;
    QLineEdit *lineEdit_Limit_Move_Time;
    QCheckBox *checkBox_show_threat;
    QLabel *label_comp1_level;
    QLineEdit *lineEdit_show_tip_sec;
    QLabel *label;
    QCheckBox *checkBox_show_tip;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_delay_between_moves_sec;
    QSlider *horizontalSlider_options_comp1_level;
    QLabel *label_4;
    QCheckBox *checkBox_1_is_comp;
    QLabel *label_6;
    QLineEdit *lineEdit_search_depth;
    QLabel *label_7;
    QLineEdit *lineEdit_moves_search_range;
    QLabel *label_8;
    QLineEdit *lineEdit_player_0_name;
    QLabel *label_9;
    QLineEdit *lineEdit_player_1_name;
    QGroupBox *groupBox_Chips_View;
    QPushButton *pushButton_chip_view_0;
    QPushButton *pushButton_chip_view_1;

    void setupUi(QDialog *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QString::fromUtf8("Options"));
        Options->resize(463, 577);
        checkBox_Skip_Confirmation = new QCheckBox(Options);
        checkBox_Skip_Confirmation->setObjectName(QString::fromUtf8("checkBox_Skip_Confirmation"));
        checkBox_Skip_Confirmation->setGeometry(QRect(30, 490, 121, 18));
        checkBox_Skip_Confirmation->setChecked(true);
        pushButton_OK = new QPushButton(Options);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(350, 530, 75, 23));
        pushButton_Cancel = new QPushButton(Options);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(30, 530, 75, 23));
        groupBox_Game_Config = new QGroupBox(Options);
        groupBox_Game_Config->setObjectName(QString::fromUtf8("groupBox_Game_Config"));
        groupBox_Game_Config->setGeometry(QRect(20, 10, 201, 121));
        groupBox_Game_Config->setFlat(false);
        groupBox_Game_Config->setCheckable(false);
        lineEdit_board_size = new QLineEdit(groupBox_Game_Config);
        lineEdit_board_size->setObjectName(QString::fromUtf8("lineEdit_board_size"));
        lineEdit_board_size->setGeometry(QRect(130, 30, 51, 20));
        lineEdit_board_size->setMaxLength(2);
        label_board_size = new QLabel(groupBox_Game_Config);
        label_board_size->setObjectName(QString::fromUtf8("label_board_size"));
        label_board_size->setGeometry(QRect(10, 30, 101, 16));
        label_required_length = new QLabel(groupBox_Game_Config);
        label_required_length->setObjectName(QString::fromUtf8("label_required_length"));
        label_required_length->setGeometry(QRect(10, 90, 111, 16));
        lineEdit_required_length = new QLineEdit(groupBox_Game_Config);
        lineEdit_required_length->setObjectName(QString::fromUtf8("lineEdit_required_length"));
        lineEdit_required_length->setGeometry(QRect(130, 90, 51, 20));
        lineEdit_required_length->setMaxLength(1);
        lineEdit_chips_number = new QLineEdit(groupBox_Game_Config);
        lineEdit_chips_number->setObjectName(QString::fromUtf8("lineEdit_chips_number"));
        lineEdit_chips_number->setGeometry(QRect(130, 60, 51, 20));
        lineEdit_chips_number->setMaxLength(2);
        label_chips_number = new QLabel(groupBox_Game_Config);
        label_chips_number->setObjectName(QString::fromUtf8("label_chips_number"));
        label_chips_number->setGeometry(QRect(10, 60, 111, 16));
        groupBox_players_Level = new QGroupBox(Options);
        groupBox_players_Level->setObjectName(QString::fromUtf8("groupBox_players_Level"));
        groupBox_players_Level->setGeometry(QRect(10, 140, 421, 341));
        label_comp0_level_2 = new QLabel(groupBox_players_Level);
        label_comp0_level_2->setObjectName(QString::fromUtf8("label_comp0_level_2"));
        label_comp0_level_2->setGeometry(QRect(280, 100, 131, 20));
        horizontalSlider_options_comp0_level = new QSlider(groupBox_players_Level);
        horizontalSlider_options_comp0_level->setObjectName(QString::fromUtf8("horizontalSlider_options_comp0_level"));
        horizontalSlider_options_comp0_level->setGeometry(QRect(180, 100, 71, 16));
        horizontalSlider_options_comp0_level->setMinimum(1);
        horizontalSlider_options_comp0_level->setMaximum(6);
        horizontalSlider_options_comp0_level->setOrientation(Qt::Horizontal);
        label_comp1_level_2 = new QLabel(groupBox_players_Level);
        label_comp1_level_2->setObjectName(QString::fromUtf8("label_comp1_level_2"));
        label_comp1_level_2->setGeometry(QRect(280, 130, 131, 20));
        lineEdit_show_threat_sec = new QLineEdit(groupBox_players_Level);
        lineEdit_show_threat_sec->setObjectName(QString::fromUtf8("lineEdit_show_threat_sec"));
        lineEdit_show_threat_sec->setGeometry(QRect(130, 220, 51, 20));
        lineEdit_show_threat_sec->setMaxLength(2);
        label_comp0_level = new QLabel(groupBox_players_Level);
        label_comp0_level->setObjectName(QString::fromUtf8("label_comp0_level"));
        label_comp0_level->setGeometry(QRect(130, 100, 41, 16));
        label_comp0_level->setMinimumSize(QSize(41, 16));
        label_5 = new QLabel(groupBox_players_Level);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 160, 51, 16));
        checkBox_0_is_comp = new QCheckBox(groupBox_players_Level);
        checkBox_0_is_comp->setObjectName(QString::fromUtf8("checkBox_0_is_comp"));
        checkBox_0_is_comp->setGeometry(QRect(10, 100, 91, 18));
        checkBox_Limit_Move_Time = new QCheckBox(groupBox_players_Level);
        checkBox_Limit_Move_Time->setObjectName(QString::fromUtf8("checkBox_Limit_Move_Time"));
        checkBox_Limit_Move_Time->setGeometry(QRect(10, 160, 101, 18));
        lineEdit_Limit_Move_Time = new QLineEdit(groupBox_players_Level);
        lineEdit_Limit_Move_Time->setObjectName(QString::fromUtf8("lineEdit_Limit_Move_Time"));
        lineEdit_Limit_Move_Time->setGeometry(QRect(130, 160, 51, 20));
        lineEdit_Limit_Move_Time->setMaxLength(3);
        checkBox_show_threat = new QCheckBox(groupBox_players_Level);
        checkBox_show_threat->setObjectName(QString::fromUtf8("checkBox_show_threat"));
        checkBox_show_threat->setGeometry(QRect(10, 220, 91, 18));
        label_comp1_level = new QLabel(groupBox_players_Level);
        label_comp1_level->setObjectName(QString::fromUtf8("label_comp1_level"));
        label_comp1_level->setGeometry(QRect(130, 130, 41, 16));
        lineEdit_show_tip_sec = new QLineEdit(groupBox_players_Level);
        lineEdit_show_tip_sec->setObjectName(QString::fromUtf8("lineEdit_show_tip_sec"));
        lineEdit_show_tip_sec->setGeometry(QRect(130, 190, 51, 20));
        lineEdit_show_tip_sec->setMaxLength(2);
        label = new QLabel(groupBox_players_Level);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 220, 51, 16));
        checkBox_show_tip = new QCheckBox(groupBox_players_Level);
        checkBox_show_tip->setObjectName(QString::fromUtf8("checkBox_show_tip"));
        checkBox_show_tip->setGeometry(QRect(10, 190, 71, 18));
        label_2 = new QLabel(groupBox_players_Level);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 190, 51, 16));
        label_3 = new QLabel(groupBox_players_Level);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(200, 250, 51, 16));
        lineEdit_delay_between_moves_sec = new QLineEdit(groupBox_players_Level);
        lineEdit_delay_between_moves_sec->setObjectName(QString::fromUtf8("lineEdit_delay_between_moves_sec"));
        lineEdit_delay_between_moves_sec->setGeometry(QRect(130, 250, 51, 20));
        lineEdit_delay_between_moves_sec->setMaxLength(2);
        horizontalSlider_options_comp1_level = new QSlider(groupBox_players_Level);
        horizontalSlider_options_comp1_level->setObjectName(QString::fromUtf8("horizontalSlider_options_comp1_level"));
        horizontalSlider_options_comp1_level->setGeometry(QRect(180, 130, 71, 16));
        horizontalSlider_options_comp1_level->setMinimum(1);
        horizontalSlider_options_comp1_level->setMaximum(6);
        horizontalSlider_options_comp1_level->setValue(1);
        horizontalSlider_options_comp1_level->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(groupBox_players_Level);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 250, 91, 16));
        checkBox_1_is_comp = new QCheckBox(groupBox_players_Level);
        checkBox_1_is_comp->setObjectName(QString::fromUtf8("checkBox_1_is_comp"));
        checkBox_1_is_comp->setGeometry(QRect(10, 130, 91, 18));
        checkBox_1_is_comp->setChecked(true);
        label_6 = new QLabel(groupBox_players_Level);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 280, 101, 16));
        lineEdit_search_depth = new QLineEdit(groupBox_players_Level);
        lineEdit_search_depth->setObjectName(QString::fromUtf8("lineEdit_search_depth"));
        lineEdit_search_depth->setGeometry(QRect(130, 280, 51, 20));
        lineEdit_search_depth->setMaxLength(2);
        label_7 = new QLabel(groupBox_players_Level);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 310, 91, 16));
        lineEdit_moves_search_range = new QLineEdit(groupBox_players_Level);
        lineEdit_moves_search_range->setObjectName(QString::fromUtf8("lineEdit_moves_search_range"));
        lineEdit_moves_search_range->setGeometry(QRect(130, 310, 51, 20));
        lineEdit_moves_search_range->setMaxLength(2);
        label_8 = new QLabel(groupBox_players_Level);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 50, 46, 13));
        lineEdit_player_0_name = new QLineEdit(groupBox_players_Level);
        lineEdit_player_0_name->setObjectName(QString::fromUtf8("lineEdit_player_0_name"));
        lineEdit_player_0_name->setGeometry(QRect(70, 40, 113, 20));
        label_9 = new QLabel(groupBox_players_Level);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(230, 50, 46, 13));
        lineEdit_player_1_name = new QLineEdit(groupBox_players_Level);
        lineEdit_player_1_name->setObjectName(QString::fromUtf8("lineEdit_player_1_name"));
        lineEdit_player_1_name->setGeometry(QRect(290, 40, 113, 20));
        groupBox_Chips_View = new QGroupBox(Options);
        groupBox_Chips_View->setObjectName(QString::fromUtf8("groupBox_Chips_View"));
        groupBox_Chips_View->setGeometry(QRect(240, 10, 201, 121));
        pushButton_chip_view_0 = new QPushButton(groupBox_Chips_View);
        pushButton_chip_view_0->setObjectName(QString::fromUtf8("pushButton_chip_view_0"));
        pushButton_chip_view_0->setGeometry(QRect(30, 40, 51, 41));
        pushButton_chip_view_1 = new QPushButton(groupBox_Chips_View);
        pushButton_chip_view_1->setObjectName(QString::fromUtf8("pushButton_chip_view_1"));
        pushButton_chip_view_1->setGeometry(QRect(120, 40, 51, 41));
        QWidget::setTabOrder(lineEdit_board_size, lineEdit_chips_number);
        QWidget::setTabOrder(lineEdit_chips_number, lineEdit_required_length);
        QWidget::setTabOrder(lineEdit_required_length, checkBox_0_is_comp);
        QWidget::setTabOrder(checkBox_0_is_comp, horizontalSlider_options_comp0_level);
        QWidget::setTabOrder(horizontalSlider_options_comp0_level, checkBox_1_is_comp);
        QWidget::setTabOrder(checkBox_1_is_comp, horizontalSlider_options_comp1_level);
        QWidget::setTabOrder(horizontalSlider_options_comp1_level, checkBox_show_tip);
        QWidget::setTabOrder(checkBox_show_tip, lineEdit_show_tip_sec);
        QWidget::setTabOrder(lineEdit_show_tip_sec, checkBox_show_threat);
        QWidget::setTabOrder(checkBox_show_threat, lineEdit_show_threat_sec);
        QWidget::setTabOrder(lineEdit_show_threat_sec, lineEdit_delay_between_moves_sec);
        QWidget::setTabOrder(lineEdit_delay_between_moves_sec, checkBox_Skip_Confirmation);

        retranslateUi(Options);

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QDialog *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Dialog", 0, QApplication::UnicodeUTF8));
        checkBox_Skip_Confirmation->setText(QApplication::translate("Options", "Skip confirmation", 0, QApplication::UnicodeUTF8));
        pushButton_OK->setText(QApplication::translate("Options", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("Options", "Cancel", 0, QApplication::UnicodeUTF8));
        groupBox_Game_Config->setTitle(QApplication::translate("Options", "Game configuration", 0, QApplication::UnicodeUTF8));
        lineEdit_board_size->setText(QApplication::translate("Options", "8", 0, QApplication::UnicodeUTF8));
        label_board_size->setText(QApplication::translate("Options", "Desk size (6..12)", 0, QApplication::UnicodeUTF8));
        label_required_length->setText(QApplication::translate("Options", "Required length (2-5)", 0, QApplication::UnicodeUTF8));
        lineEdit_required_length->setText(QApplication::translate("Options", "4", 0, QApplication::UnicodeUTF8));
        lineEdit_chips_number->setText(QApplication::translate("Options", "12", 0, QApplication::UnicodeUTF8));
        label_chips_number->setText(QApplication::translate("Options", "Chips number (6..20)", 0, QApplication::UnicodeUTF8));
        groupBox_players_Level->setTitle(QApplication::translate("Options", "Players, Levels, Timing", 0, QApplication::UnicodeUTF8));
        label_comp0_level_2->setText(QApplication::translate("Options", "1 - random", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        horizontalSlider_options_comp0_level->setToolTip(QApplication::translate("Options", "Left computer side level", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_comp1_level_2->setText(QApplication::translate("Options", "1 - random", 0, QApplication::UnicodeUTF8));
        lineEdit_show_threat_sec->setText(QApplication::translate("Options", "3", 0, QApplication::UnicodeUTF8));
        label_comp0_level->setText(QApplication::translate("Options", "Level:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Options", "seconds", 0, QApplication::UnicodeUTF8));
        checkBox_0_is_comp->setText(QApplication::translate("Options", "First is comp", 0, QApplication::UnicodeUTF8));
        checkBox_Limit_Move_Time->setText(QApplication::translate("Options", "Limit move time", 0, QApplication::UnicodeUTF8));
        lineEdit_Limit_Move_Time->setText(QApplication::translate("Options", "1", 0, QApplication::UnicodeUTF8));
        checkBox_show_threat->setText(QApplication::translate("Options", "Show threat in", 0, QApplication::UnicodeUTF8));
        label_comp1_level->setText(QApplication::translate("Options", "Level:", 0, QApplication::UnicodeUTF8));
        lineEdit_show_tip_sec->setText(QApplication::translate("Options", "3", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Options", "seconds", 0, QApplication::UnicodeUTF8));
        checkBox_show_tip->setText(QApplication::translate("Options", "Show tip in", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Options", "seconds", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Options", "seconds", 0, QApplication::UnicodeUTF8));
        lineEdit_delay_between_moves_sec->setText(QApplication::translate("Options", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        horizontalSlider_options_comp1_level->setToolTip(QApplication::translate("Options", "Right computer side level", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("Options", "Delay comp moves", 0, QApplication::UnicodeUTF8));
        checkBox_1_is_comp->setText(QApplication::translate("Options", "Second is comp", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Options", "Comp search depth", 0, QApplication::UnicodeUTF8));
        lineEdit_search_depth->setText(QApplication::translate("Options", "1", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Options", "Moves range", 0, QApplication::UnicodeUTF8));
        lineEdit_moves_search_range->setText(QApplication::translate("Options", "1", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Options", "Player 0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Options", "Player 1", 0, QApplication::UnicodeUTF8));
        groupBox_Chips_View->setTitle(QApplication::translate("Options", "Chips view", 0, QApplication::UnicodeUTF8));
        pushButton_chip_view_0->setText(QApplication::translate("Options", "Left", 0, QApplication::UnicodeUTF8));
        pushButton_chip_view_1->setText(QApplication::translate("Options", "Right", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
