// --------------------------------------------------------------------
// chip_options.h
// --------------------------------------------------------------------

#ifndef CHIP_OPTIONS_H
#define CHIP_OPTIONS_H

#include <QDialog>
#include <QColor>
#include <QPainter>

#include "types_int.h"
#include "configuration_typedef.h"
#include "pushbutton_chip.h"

namespace Ui {
class chip_options;
}

class chip_options : public QDialog
{
    Q_OBJECT
    
public:
    explicit chip_options(
                bool player,
                CONFIGURATION_USERDEF* m_pConfiguration,
                QWidget *parent = 0);
    ~chip_options();

private slots:
    //void on_select_color_clicked();
    void clickedSlot ();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_radioButton_shape_round_released();
    void on_radioButton_shape_square_released();
    void on_radioButton_shape_triangle_released();
    void on_radioButton_shape_xo_released();

private:
    bool player;
    CONFIGURATION_USERDEF* m_pConfiguration;
    SHAPE_KIND Current_Shape;
    QColor Current_Color;

    pushbutton_chip* pChip;

    Ui::chip_options *ui;
};

#endif // CHIP_OPTIONS_H
