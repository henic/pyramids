// --------------------------------------------------------------------
// options.h
// --------------------------------------------------------------------

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

#include "configuration_typedef.h"

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT
    
public:
    explicit Options(
                   CONFIGURATION_USERDEF* pInitialConfiguration,
                   bool GameIsActive,
                   QWidget *parent = 0);
    ~Options();
    
    CONFIGURATION_USERDEF* Get_Updated_Configuration (void);

private slots:
    void on_pushButton_Cancel_clicked();
    void on_pushButton_OK_clicked();

    void on_checkBox_show_tip_stateChanged(int arg1);
    void on_checkBox_show_threat_stateChanged(int arg1);
    void on_checkBox_0_is_comp_stateChanged(int arg1);
    void on_checkBox_1_is_comp_stateChanged(int arg1);
    void on_checkBox_Limit_Move_Time_stateChanged(int arg1);

    void on_horizontalSlider_options_comp0_level_valueChanged(int value);
    void on_horizontalSlider_options_comp1_level_valueChanged(int value);

    void on_pushButton_chip_view_0_clicked();
    void on_pushButton_chip_view_1_clicked();

    void mouseReleaseEvent(QMouseEvent* pMouseEvent);

private:
    QString level_to_string (int value);
    void Get_Cfg            (void);
    void Show_Cfg           (void);
    void Enable_Disable_Set (void);
private:
    Ui::Options *ui;
    bool m_Game_Is_Active;
    CONFIGURATION_USERDEF* m_pConfiguration;
};

#endif // OPTIONS_H
