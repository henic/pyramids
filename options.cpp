// --------------------------------------------------------------------
// options.cpp
// --------------------------------------------------------------------

#include <QDebug>

#include "configuration_typedef.h"
#include "options.h"
#include "ui_options.h"
#include "chip_options.h"

static const    quint16 Max_Comp_Level = 6;

// --------------------------------------------------------------------
void Options::Show_Cfg (void)
{
    qDebug() << "Options::Show_Cfg";

    // init sliders of computer level
    ui->horizontalSlider_options_comp0_level->setRange(1, Max_Comp_Level);
    ui->horizontalSlider_options_comp1_level->setRange(1, Max_Comp_Level);

    // default data
    ui->lineEdit_board_size->setText(
                QString::number(m_pConfiguration->Board_Size));
    ui->lineEdit_chips_number->setText(
                QString::number(m_pConfiguration->Chips_Number));
    ui->lineEdit_required_length->setText(
                QString::number(m_pConfiguration->Chain_Length));

    // 0_is_comp
    ui->checkBox_0_is_comp->setChecked(m_pConfiguration->First_Is_Computer);
    ui->horizontalSlider_options_comp0_level->setValue(
                                m_pConfiguration->First_Computer_Level);
    emit (on_horizontalSlider_options_comp1_level_valueChanged(
                                m_pConfiguration->First_Computer_Level));

    // 1_is_comp
    ui->checkBox_1_is_comp->setChecked(m_pConfiguration->Second_Is_Computer);
    ui->horizontalSlider_options_comp1_level->setValue(
                                m_pConfiguration->Second_Computer_Level);
    emit (on_horizontalSlider_options_comp0_level_valueChanged(
                                m_pConfiguration->Second_Computer_Level));

    // show_tip
    ui->checkBox_show_tip->setChecked(m_pConfiguration->Show_Tip);
    ui->lineEdit_show_tip_sec->setText(
                QString::number(m_pConfiguration->Delay_Show_Tip));

    // show_threat
    ui->checkBox_show_threat->setChecked(m_pConfiguration->Show_Threat);
    ui->lineEdit_show_threat_sec->setText(
                QString::number(m_pConfiguration->Delay_Show_Threat));

    // limit_move_time
    ui->checkBox_Limit_Move_Time->setChecked(
                m_pConfiguration->Limit_Move_Time);
    ui->lineEdit_Limit_Move_Time->setText(
                QString::number(m_pConfiguration->Limit_Move_Time_Sec));

    // delay between moves
    ui->lineEdit_delay_between_moves_sec->setText(
             QString::number(m_pConfiguration->Delay_Betweeen_Computer_Moves));

    ui->lineEdit_search_depth->setText(
                QString::number(m_pConfiguration->Comp_Search_Depth));
    ui->lineEdit_moves_search_range->setText(
                QString::number(m_pConfiguration->Moves_Search_Range));

    ui->lineEdit_player_0_name->setText(m_pConfiguration->Player_0_Name);
    ui->lineEdit_player_1_name->setText(m_pConfiguration->Player_1_Name);

    // skip confirmation
    ui->checkBox_Skip_Confirmation->setChecked(
             m_pConfiguration->Skip_Confirmation);

}

// --------------------------------------------------------------------
void Options::Enable_Disable_Set (void)
{
    qDebug() << "Options::Enable_Disable_Set";

    // depends only on local configuration structure

    // ---------------------------------------
    // actions according current configuration
    // ---------------------------------------
    bool Both_Are_Comp =
            m_pConfiguration->First_Is_Computer &&
            m_pConfiguration->Second_Is_Computer;

    bool Any_Is_Comp =
            m_pConfiguration->First_Is_Computer ||
            m_pConfiguration->Second_Is_Computer;

    bool Any_Is_Human = ! Both_Are_Comp;

    bool Enable_Level_Change = !m_Game_Is_Active;

    // ---------------------------------------
    // delay between moves - only if any_is_comp
    ui->lineEdit_delay_between_moves_sec->setEnabled(Any_Is_Comp);


    // board size, chips number
    ui->lineEdit_board_size->       setEnabled(Enable_Level_Change);
    ui->lineEdit_chips_number->     setEnabled(Enable_Level_Change);
    ui->lineEdit_required_length->  setEnabled(Enable_Level_Change);

    // 0 is computer
    ui->checkBox_0_is_comp->        setEnabled(Enable_Level_Change);
    ui->horizontalSlider_options_comp0_level->setEnabled(
                m_pConfiguration->First_Is_Computer);

    // 1 is computer
    ui->checkBox_1_is_comp->        setEnabled(Enable_Level_Change);
    ui->horizontalSlider_options_comp1_level->setEnabled(
                m_pConfiguration->Second_Is_Computer);

    // ---------------------------------------
    ui->lineEdit_Limit_Move_Time->setEnabled(
                m_pConfiguration->Limit_Move_Time && Any_Is_Comp);
    ui->checkBox_Limit_Move_Time->setEnabled(Any_Is_Comp);
    ui->checkBox_Limit_Move_Time->setChecked(
                m_pConfiguration->Limit_Move_Time && Any_Is_Comp);

    // ---------------------------------------
    ui->checkBox_show_threat->setEnabled(Any_Is_Human);
    ui->checkBox_show_threat->setChecked(
                Any_Is_Human && m_pConfiguration->Show_Threat);
    ui->lineEdit_show_threat_sec->setEnabled(
                Any_Is_Human && m_pConfiguration->Show_Threat);

    // ---------------------------------------
    ui->checkBox_show_tip->setEnabled(Any_Is_Human);
    ui->checkBox_show_tip->setChecked(
                Any_Is_Human && m_pConfiguration->Show_Tip);
    ui->lineEdit_show_tip_sec->setEnabled(
                Any_Is_Human && m_pConfiguration->Show_Tip);
}

// --------------------------------------------------------------------
Options::Options (
            CONFIGURATION_USERDEF* pInitialConfiguration,
            bool Game_Is_Active,
            QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    qDebug("Options constructor");

    ui->setupUi(this);

    m_Game_Is_Active = Game_Is_Active;

    m_pConfiguration = (CONFIGURATION_USERDEF*) malloc (sizeof (CONFIGURATION_USERDEF));
    if (m_pConfiguration==NULL) {
        qDebug("Options: Malloc failed");
        return;
    }
    memcpy(m_pConfiguration, pInitialConfiguration, sizeof(CONFIGURATION_USERDEF));

    Show_Cfg();
    Enable_Disable_Set ();
}

Options::~Options()
{
    if (m_pConfiguration!=NULL) {
        free (m_pConfiguration);
        m_pConfiguration = NULL;
    }
    delete ui;
}

void Options::on_pushButton_Cancel_clicked()
{
    reject();
    close ();
}

void Options::on_pushButton_OK_clicked()
{
    Get_Cfg (); // copy to result structure
    accept();
    close ();
}

// --------------------------------------------------------------------
CONFIGURATION_USERDEF* Options::Get_Updated_Configuration (void) {
    return m_pConfiguration;
}

// --------------------------------------------------------------------
// copy from window to result structure
void Options::Get_Cfg(void)
{
    m_pConfiguration->Chips_Number          =
            ui->lineEdit_chips_number->text().toUShort();
    m_pConfiguration->Board_Size             =
            ui->lineEdit_board_size->text().toUShort();
    m_pConfiguration->Chain_Length =
            ui->lineEdit_required_length->text().toUShort();
    m_pConfiguration->First_Is_Computer     =
            ui->checkBox_0_is_comp->isChecked();
    m_pConfiguration->First_Computer_Level  =
            ui->horizontalSlider_options_comp0_level->value();
    m_pConfiguration->Second_Is_Computer    =
            ui->checkBox_1_is_comp->isChecked();
    m_pConfiguration->Second_Computer_Level =
            ui->horizontalSlider_options_comp1_level->value();
    m_pConfiguration->Show_Tip              =
            ui->checkBox_show_tip->isChecked();
    m_pConfiguration->Delay_Show_Tip        =
            ui->lineEdit_show_tip_sec->text().toUShort();
    m_pConfiguration->Show_Threat           =
            ui->checkBox_show_threat->isChecked();
    m_pConfiguration->Delay_Show_Threat     =
            ui->lineEdit_show_threat_sec->text().toUShort();
    m_pConfiguration->Limit_Move_Time       =
            ui->checkBox_Limit_Move_Time->isChecked();
    m_pConfiguration->Limit_Move_Time_Sec   =
            ui->lineEdit_Limit_Move_Time->text().toUShort();
    m_pConfiguration->Delay_Betweeen_Computer_Moves =
            ui->lineEdit_delay_between_moves_sec->text().toUShort();
    m_pConfiguration->Comp_Search_Depth =
            ui->lineEdit_search_depth->text().toUShort();
    m_pConfiguration->Moves_Search_Range =
            ui->lineEdit_moves_search_range->text().toUShort();
    m_pConfiguration->Skip_Confirmation     =
            ui->checkBox_Skip_Confirmation->isChecked();
    m_pConfiguration->Player_0_Name = ui->lineEdit_player_0_name->text();
    m_pConfiguration->Player_1_Name = ui->lineEdit_player_1_name->text();

    // chips number no more of total cells number
    if (m_pConfiguration->Chips_Number > m_pConfiguration->Board_Size*m_pConfiguration->Board_Size/2)
        m_pConfiguration->Chips_Number = m_pConfiguration->Board_Size*m_pConfiguration->Board_Size/2;
}

// --------------------------------------------------------------------
void Options::on_checkBox_show_tip_stateChanged(int arg1)
{
    ui->lineEdit_show_tip_sec->setEnabled(arg1);
}

// --------------------------------------------------------------------
void Options::on_checkBox_show_threat_stateChanged(int arg1)
{
    ui->lineEdit_show_threat_sec->setEnabled(arg1);
}

// --------------------------------------------------------------------
void Options::on_checkBox_Limit_Move_Time_stateChanged(int arg1)
{
    m_pConfiguration->Limit_Move_Time = true;
    ui->lineEdit_Limit_Move_Time->setEnabled(arg1);
}

// --------------------------------------------------------------------
void Options::on_checkBox_0_is_comp_stateChanged(int arg1)
{
    qDebug() << "Options::on_checkBox_0_is_comp_stateChanged " << arg1;
    m_pConfiguration->First_Is_Computer = arg1;
    Enable_Disable_Set();
}

// --------------------------------------------------------------------
void Options::on_checkBox_1_is_comp_stateChanged(int arg1)
{
    qDebug() << "Options::on_checkBox_1_is_comp_stateChanged " << arg1;
    m_pConfiguration->Second_Is_Computer = arg1;
    Enable_Disable_Set();
}

// --------------------------------------------------------------------
QString Options::level_to_string (int value) {
    static QString Result;
    switch (value) {
    case 1:
        Result = "1 - random";
        break;
    case 2:
        Result = "2 - random, max neighbors";
        break;
    case 3:
        Result = "3 - longest chain";
        break;
    case 4:
        Result = "4 - threat+chain";
        break;
    case 5:
        Result = "5 - heuristic";
        break;
    case 6:
        Result = "6 - bruteforce";
        break;
    default:
        Result = QString::number(value) + " - Unknown";
        break;
    }
    return Result;
}

// --------------------------------------------------------------------
void Options::on_horizontalSlider_options_comp0_level_valueChanged(int value)
{

    ui->label_comp0_level_2->setText(level_to_string(value));
}

// --------------------------------------------------------------------
void Options::on_horizontalSlider_options_comp1_level_valueChanged(int value)
{
     ui->label_comp1_level_2->setText(level_to_string(value));
}

// --------------------------------------------------------------------
void Options::on_pushButton_chip_view_0_clicked()
{
    chip_options chipview (0, m_pConfiguration, this);
    chipview.exec();
}

// --------------------------------------------------------------------
void Options::on_pushButton_chip_view_1_clicked()
{
    chip_options chipview (1, m_pConfiguration, this);
    chipview.exec();
}


// --------------------------------------------------------------------
void Options::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
    qDebug() << "options:mouse";
    QWidget::mouseReleaseEvent(pMouseEvent);
}
