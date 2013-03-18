// ------------------------------------------------------
// board.h
// ------------------------------------------------------

#ifndef BOARD_H
#define BOARD_H

// ------------------------------------------------------
#include <QColor>
#include <QGridLayout>
#include <QPoint>
#include <QVector>

#include "const_int.h"
#include "configuration_typedef.h"
#include "cell.h"

// ------------------------------------------------------
class Board : public QWidget
{
    Q_OBJECT

public:
    static const quint16 range_for_move;

public:
    Board (CONFIGURATION_USERDEF& Configuration_Data,
           const QRect& Rect,
           QWidget* pParent = 0,
           Qt::WindowFlags Flag = Qt::Widget);
    ~Board (void);

    void Reset              (void);
    bool Is_Final_Position  (QPoint last_added_coord, quint16 required_chain);
    int  Occupy_Cell        (quint16 col, quint16 row, bool owner);
    int  Free_Cell          (quint16 col, quint16 row);
    int  Set_Chip_View      (bool owner, SHAPE_KIND shape_kind, QColor color);
    int  Cell_Is_Occupied   (quint16 col, quint16 row);
    int  Cell_Get_Owner     (quint16 col, quint16 row);
    int  Access_To_Cell     (quint16 col, quint16 row, Cell** pCell);
    void Possible_Moves_update (const quint16 col, const quint16 row);
    int  Cell_Set_Possible_Move (quint16 col, quint16 row, bool value);
    int  Cell_Get_Possible_Move (quint16 col, quint16 row);
    void Possible_Moves_print   (void);

private:

    QVector<QVector<Cell*> >  Cells;  // 2-dimensional array

    quint16     board_size;
    QPoint      center;

    quint16     cell_width, cell_height;

    SHAPE_KIND  chip0_shape; // round, triangle, square, x/o
    QColor      chip0_color;

    SHAPE_KIND  chip1_shape; // round, triangle, square, x/o
    QColor      chip1_color;

};

#endif // BOARD_H
