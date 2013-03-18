// --------------------------------------------------------------------
// pushbutton_chip.cpp
// --------------------------------------------------------------------

#include <QDebug>
#include <QPainter>

#include "pushbutton_chip.h"
#include "serv.h"

//-----------------------------------------------------------
pushbutton_chip::pushbutton_chip (SHAPE_KIND shape,
                                  QColor chip_color, QColor bg_color, QColor grid_color,
                                  QWidget *parent) :
    QPushButton(parent)
{
    qDebug() << "pushbutton_chip constructor shape=" << Shape_Kind_To_Str(shape);
    this->bg_color = bg_color;
    this->grid_color = grid_color;
    Chip_Set (shape, chip_color);
}

//-----------------------------------------------------------
void pushbutton_chip::Chip_Set (
          SHAPE_KIND shape,
          QColor chip_color)
{
    this->shape         = shape;
    this->chip_color    = chip_color;
    update ();
}

//-----------------------------------------------------------
void pushbutton_chip::Draw_Chip (QPainter& painter)
{
    //qDebug("pushbutton_chip::draw_chip, shape=%s",
    //       qPrintable (Shape_Kind_To_Str(shape)));

    QRect button_rect = rect();
    quint16 quater_x = button_rect.width()>>2;
    quint16 quater_y = button_rect.height()>>2;

    QPoint center_coord = QPoint (button_rect.width()/2,
                                  button_rect.height()/2);

    painter.fillRect(button_rect, bg_color);

    painter.setBrush(chip_color);

    switch (shape) {

    case SHAPE_UNDEFINED:
        break;

    case SHAPE_ROUND:
        qDebug() << "center="  << qPrintable(Point_Coord_To_Str(center_coord)) <<
                    "radius=" << qPrintable(Coord_To_Str(quater_x, quater_y));
        painter.drawEllipse(center_coord, quater_x, quater_y);
        break;

    case SHAPE_SQUARE:
    {
        QRect r (QPoint (quater_x,   quater_y),
                 QPoint (quater_x*3, quater_y*3));
        painter.fillRect(r, chip_color);
    }
        break;

    case SHAPE_TRIANGLE:
    {
        QPoint p[3];
        p[0].setX (quater_x);
        p[0].setY (quater_y*3);

        p[1].setX(center_coord.x());
        p[1].setY(quater_y);

        p[2].setX(quater_x*3);
        p[2].setY(p[0].y());
        qDebug ("Triangle: %s - %s - %s",
                    qPrintable(Point_Coord_To_Str(p[0])),
                    qPrintable(Point_Coord_To_Str(p[1])),
                    qPrintable(Point_Coord_To_Str(p[2])));
        painter.drawPolygon(p, 3, Qt::OddEvenFill);
        break;
    }

    case SHAPE_XO:
        if (rand()&1) {    // draw O
            painter.setBrush( Qt::NoBrush );
            painter.drawEllipse(center_coord, quater_x, quater_y);
        }
        else {          // draw X
            painter.drawLine(QPoint (quater_x,   quater_y),
                             QPoint (quater_x*3, quater_y*3));
            painter.drawLine(QPoint (quater_x*3, quater_y),
                             QPoint (quater_x,   quater_y*3));
        }
        break;

    default:
        qCritical() <<
                       "pushbutton_chip::draw_chip: unknown shape value" <<
                       (int) shape;
        break;
    }
}

// -------------------------------------------------
void pushbutton_chip::Draw_Borders (QPainter& painter) {

    painter.setBrush(grid_color);
    //painter.drawRect (rect());
    QRect r = rect();
    painter.drawLine(r.topLeft(),    r.topRight());
    painter.drawLine(r.topLeft(),    r.bottomLeft());
    painter.drawLine(r.bottomLeft(), r.bottomRight());
    painter.drawLine(r.topRight(),   r.bottomRight());
}

// -------------------------------------------------
void pushbutton_chip::paintEvent(QPaintEvent *event)
{
    //qDebug() << "pushbutton_chip::paintEvent";
    QPainter painter(this);
    Draw_Chip(painter);
    Draw_Borders(painter);
    QWidget::paintEvent(event);
}
