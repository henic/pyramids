// --------------------------------------------------------------------
// pushbutton_chip.h
// --------------------------------------------------------------------

#ifndef PUSHBUTTON_CHIP_H
#define PUSHBUTTON_CHIP_H

#include <QPushButton>

#include "types_int.h"

class pushbutton_chip : public QPushButton
{
    Q_OBJECT

public:
    pushbutton_chip (SHAPE_KIND shape,
                     QColor chip_color, QColor bg_color, QColor grid_color,
                     QWidget *parent);

    void Chip_Set (SHAPE_KIND shape, QColor chip_color);

signals:


private:
    SHAPE_KIND shape;
    QColor chip_color;
    QColor bg_color; QColor grid_color;

private:
    void Draw_Borders (QPainter& painter);
    void Draw_Chip    (QPainter& painter);

private slots:
    void paintEvent(QPaintEvent *event);

public slots:
    
};

#endif // PUSHBUTTON_CHIP_H
