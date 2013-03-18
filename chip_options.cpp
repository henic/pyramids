// --------------------------------------------------------------------
// chip_options.cpp
// --------------------------------------------------------------------

#include <QColorDialog>
#include <QDebug>
#include <QPainter>
#include <QWidget>

#include "chip_options.h"
#include "ui_chip_options.h"

#include "types_int.h"
#include "configuration_typedef.h"
#include "cell.h"

// --------------------------------------------------------------------
chip_options::chip_options (bool player,
                            CONFIGURATION_USERDEF* m_pConfiguration,
                            QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chip_options)
{
    this->player = player;
    this->m_pConfiguration = m_pConfiguration;

    ui->setupUi(this);

    // init data:
    Current_Shape = player ?
                    m_pConfiguration->Chip1_Shape :
                    m_pConfiguration->Chip0_Shape;
    Current_Color = player ?
                    m_pConfiguration->Chip1_Color :
                    m_pConfiguration->Chip0_Color;

    pChip = new pushbutton_chip (
                    Current_Shape, Current_Color,
                    Cell::bg_color, Cell::grid_color,
                    this);

    pChip->setGeometry(QRect(140, 20, 121, 121)); //remove! should update

    switch (Current_Shape) {
    case SHAPE_ROUND:
        ui->radioButton_shape_round->setChecked(1);
        emit (on_radioButton_shape_round_released());
        break;
    case SHAPE_SQUARE:
        ui->radioButton_shape_square->setChecked(1);
        emit (on_radioButton_shape_square_released());
        break;
    case SHAPE_TRIANGLE:
        ui->radioButton_shape_triangle->setChecked(1);
        emit (on_radioButton_shape_triangle_released());
        break;
    case SHAPE_XO:
        ui->radioButton_shape_xo->setChecked(1);
        emit (on_radioButton_shape_xo_released());
        break;
    default: break;
    }

    connect(pChip, SIGNAL(clicked()), this,
            SLOT(clickedSlot()));
    pChip->show();
}

// -------------------------------------------------
chip_options::~chip_options()
{
    delete ui;
}

// -------------------------------------------------
void chip_options::clickedSlot()
{
    qDebug() << "chip_options::clickedSlot";
    QColor color = QColorDialog::getColor(Current_Color, this);
    if (color.isValid()) {
        //pChip->setText(color.name());
        pChip->setPalette(QPalette(color));
        pChip->setAutoFillBackground(true);
        Current_Color = color;
        pChip->Chip_Set (Current_Shape, Current_Color);
        pChip->update();
    }
}


// -------------------------------------------------
void chip_options::on_buttonBox_accepted()
{
    // apply and close - should we save config?
    if (player) {
        m_pConfiguration->Chip1_Color = Current_Color;
        m_pConfiguration->Chip1_Shape = Current_Shape;
    } else {
        m_pConfiguration->Chip0_Color = Current_Color;
        m_pConfiguration->Chip0_Shape = Current_Shape;
    }

    close ();
}

// -------------------------------------------------
void chip_options::on_buttonBox_rejected()
{
    close ();
}

// -------------------------------------------------
void chip_options::on_radioButton_shape_round_released()
{
    Current_Shape = SHAPE_ROUND;
    pChip->Chip_Set (Current_Shape, Current_Color);
}

// -------------------------------------------------
void chip_options::on_radioButton_shape_square_released()
{
    Current_Shape = SHAPE_SQUARE;
    pChip->Chip_Set (Current_Shape, Current_Color);
}

// -------------------------------------------------
void chip_options::on_radioButton_shape_triangle_released()
{
    Current_Shape = SHAPE_TRIANGLE;
    pChip->Chip_Set (Current_Shape, Current_Color);
}

// -------------------------------------------------
void chip_options::on_radioButton_shape_xo_released()
{
    Current_Shape = SHAPE_XO;
    pChip->Chip_Set (Current_Shape, Current_Color);
}

// -------------------------------------------------
