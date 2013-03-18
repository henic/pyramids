//-----------------------------------------------------------
// cell.h
//-----------------------------------------------------------

#ifndef CELL_H
#define CELL_H

//-----------------------------------------------------------
#include <QMouseEvent>
#include <QWidget>
#include <QPoint>
#include <QLabel>

#include "const_int.h"
#include "types_int.h"

//#define invalid_ushort 1870

// ------------------------------------------------------
class Cell : public QLabel
{
    Q_OBJECT

public:
    Cell(quint16 col, quint16 row,
         QRect cell_rect,
         QPoint board_center,
         QWidget* parent = 0);
    ~Cell ();

    int  Occupy (bool owner,
                 SHAPE_KIND shape, QColor color,
                 quint16 col, quint16 row);
    int  Free        (void);
    int  Is_Occupied (void);
    int  Get_Owner   (void);
    void Set_Blink   (void); // time and color are constants
    void Set_Possible_Move (bool value);
    int  Get_Possible_Move (void);

private:
    void Draw_Chip    (QPainter& painter);
    void Draw_Borders (QPainter& painter);

signals:
    void clicked (int, int);

private slots:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent (QMouseEvent*);
    void restore_colors (void);

public:
    static const QColor bg_color;
    static const QColor grid_color;
    static const QColor win_color;

    static const quint16 blink_time;

private:
    bool    occupied;
    bool    owner;
    bool    possible_move;

    quint16 col, row;

    SHAPE_KIND  shape;
    QColor      chip_color;
    QColor      saved_chip_color;

    // these fields are set only during initialization
    float   dist_to_center;
    QPoint  center_coord, top_left, bottom_right;

};

// ------------------------------------------------------

#endif // CELL_H
