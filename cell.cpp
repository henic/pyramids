// --------------------------------------------------------------------
// cell.cpp
// --------------------------------------------------------------------

#include <math.h>

#include <QDebug>
#include <QPainter>
#include <QRect>
#include <QTimer>

#include "const_int.h"
#include "types_int.h"
#include "cell.h"
#include "serv.h"

// --------------------------------------------------------------------
const QColor Cell::bg_color     = Qt::gray;
const QColor Cell::grid_color   = Qt::black;
const QColor Cell::win_color    = QColor (127,255,0);

const quint16 Cell::blink_time  = 1000;

// --------------------------------------------------------------------
Cell::Cell(quint16 col, quint16 row,
           QRect cell_rect,
           QPoint board_center,
           QWidget* parent)
                : QLabel(parent)
{
    quint16 dist_x = abs (col - board_center.x());
    quint16 dist_y = abs (row - board_center.y());
    dist_to_center = sqrt (dist_x*dist_x + dist_y*dist_y);

    top_left       = cell_rect.topLeft();
    bottom_right   = cell_rect.bottomRight();

    center_coord.rx() = cell_rect.width()>>1;
    center_coord.ry() = cell_rect.height()>>1;

    occupied = false;
    owner    = 0; // n/a
    possible_move = false;
    this->col = col;
    this->row = row;

    setAlignment(Qt::AlignCenter);
    setAutoFillBackground(true);
    setScaledContents(true);
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(3);
    shape        = SHAPE_UNDEFINED;
    chip_color   = Qt::white;
    show();
}

// --------------------------------------------------------------------
Cell::~Cell()
{

}

//-----------------------------------------------------------
int Cell::Occupy (bool owner,
                  SHAPE_KIND shape, QColor color,
                  quint16 row, quint16 col)
{
    occupied    = true;
    this->owner = owner;
    //possible_move = false; will be updated automatically

    this->row   = row;
    this->col   = col;

    this->shape      = shape;
    this->chip_color = color;

    update ();
    return 0;
}

//-----------------------------------------------------------
int Cell::Free (void) {
    occupied = false;

    update ();
    return 0;
}

//-----------------------------------------------------------
int  Cell::Is_Occupied (void) {return occupied;}
int  Cell::Get_Owner   (void) {return owner;}
void Cell::Set_Possible_Move (bool value) {possible_move = value;}
int  Cell::Get_Possible_Move (void) {return possible_move;}

//-----------------------------------------------------------
void Cell::Draw_Chip (QPainter& painter) {
    qDebug() << "Draw_Chip" << qPrintable(Coord_To_Str(col, row)) <<
                "shape=" << Shape_Kind_To_Str(shape);

    quint16 quater_x = this->width()>>2;
    quint16 quater_y = height()>>2;

    switch (shape) {

    case SHAPE_UNDEFINED:
        break;

    case SHAPE_ROUND:
        painter.setBrush(chip_color);
        painter.drawEllipse(center_coord, quater_x, quater_y);
        break;

    case SHAPE_SQUARE:
    {
        QRect r (QPoint (rect().left()+quater_x, rect().top()+quater_y),
                 QPoint (rect().left()+3*quater_x, rect().top()+3*quater_y));
        painter.fillRect(r, chip_color);
        //painter.setBrush(grid_color);
        painter.drawRect(r);
    }
        break;

    case SHAPE_TRIANGLE:
    {
        QPoint p[3];
        p[0].setX (rect().left() +quater_x);
        p[0].setY (rect().top()+3*quater_y);

        p[1].setX(center_coord.x());
        p[1].setY(rect().top()+quater_y);

        p[2].setX(rect().left()+3*quater_x);
        p[2].setY(p[0].y());
        painter.setBrush(chip_color);
        painter.drawPolygon(p, 3, Qt::OddEvenFill);
        break;
    }
    case SHAPE_XO:
        if (owner) {    // draw O
            painter.drawEllipse(center_coord, quater_x, quater_y);
        }
        else {          // draw X
            painter.drawLine(QPoint (rect().left()+quater_x,
                                     rect().top()+quater_y),
                             QPoint (rect().left()+3*quater_x,
                                     rect().top()+3*quater_y));
            painter.drawLine(QPoint (rect().left()+3*quater_x,
                                     rect().top()+quater_y),
                             QPoint (rect().left()+quater_x,
                                     rect().top()+3*quater_y));
        }
        break;

    default:
        qCritical() << "Cell::Draw_Chip: unknown shape value" << (int) shape;
        break;

    }
}

// --------------------------------------------------------------------
void Cell::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
    if(rect().contains(pMouseEvent->pos()))
    {
        if (! occupied)
        {
            emit this->clicked(col, row);
        }
    }

    QWidget::mouseReleaseEvent(pMouseEvent);
}

// -------------------------------------------------
void Cell::Draw_Borders (QPainter& painter)
{
    //painter.drawRect (rect());
    painter.drawLine(rect().topLeft(),    rect().topRight());
    painter.drawLine(rect().topLeft(),    rect().bottomLeft());
    painter.drawLine(rect().bottomLeft(), rect().bottomRight());
    painter.drawLine(rect().topRight(),   rect().bottomRight());
}

// -------------------------------------------------
void Cell::paintEvent(QPaintEvent *event)
{
    //qDebug() << "Cell::paintEvent";
    QPainter painter(this);
    painter.setBackground(Qt::CrossPattern);

    painter.fillRect(rect(), QBrush(bg_color));

    if (Is_Occupied())
        Draw_Chip(painter);
    Draw_Borders(painter);

    QWidget::paintEvent(event);
}

// -------------------------------------------------
// blinking
// -------------------------------------------------
void Cell::Set_Blink   (void)
{
    qDebug() << "Set_Blink" << qPrintable(Coord_To_Str(col, row));
    saved_chip_color = chip_color;
    chip_color = win_color;
    QTimer::singleShot (blink_time, this, SLOT(restore_colors()));
    update ();
}

// -------------------------------------------------
void Cell::restore_colors(void)
{
    qDebug() << "restore_colors" << qPrintable(Coord_To_Str(col, row));
    chip_color = saved_chip_color;
    update();
}

