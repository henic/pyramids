// --------------------------------------------------------------------
// board.cpp
// --------------------------------------------------------------------

#include <QPainter>
#include <QDebug>

#include "configuration_typedef.h"
#include "board.h"
#include "serv.h"

const quint16 Board::range_for_move = 2;

// --------------------------------------------------------------------
Board::Board (CONFIGURATION_USERDEF& Configuration_Data,
              const QRect& Rect,
              QWidget* pParent, Qt::WindowFlags Flag)
    : QWidget(pParent, Flag)
{
    this->setGeometry(Rect);

    // ---- set internal variables ----
    board_size = Configuration_Data.Board_Size;
    qDebug() << "Board constructor, size=" << board_size;
    if (board_size==0)
        return;
    center = QPoint (board_size>>1, board_size>>1);

    quint16 board_width  = this->rect().width();
    quint16 board_height = this->rect().height();
    qDebug() << "Board size=" << qPrintable(Coord_To_Str(board_width, board_height));

    cell_width  = board_width  / board_size;
    cell_height = board_height / board_size;
    qDebug() << "Cell size=" << qPrintable(Coord_To_Str (cell_width, cell_height));

    chip0_shape = (SHAPE_KIND) Configuration_Data.Chip0_Shape;
    chip0_color = Configuration_Data.Chip0_Color;
    chip1_shape = (SHAPE_KIND) Configuration_Data.Chip1_Shape;
    chip1_color = Configuration_Data.Chip1_Color;

    // ---- init cells array ----
    Cells.resize(board_size);
    for (quint16 i=0; i<board_size; i++)
        Cells[i].resize(board_size);

    for (quint16 i=0; i<board_size; i++)
    for (quint16 j=0; j<board_size; j++) {
        QRect cell_rect;
        cell_rect.setLeft   (cell_width*i);
        cell_rect.setRight  (cell_width*(i+1));
        cell_rect.setTop    (cell_height*j);
        cell_rect.setBottom (cell_height*(j+1));

        Cell *pCell = new Cell(i, j,
                               cell_rect,
                               center,
                               this);
        pCell->setGeometry(cell_rect);
        Cells[i][j] = pCell;
    }

    this->show();

}

// --------------------------------------------------------------------
Board::~Board (void) {
    for (quint16 i=0; i<board_size; i++)
    for (quint16 j=0; j<board_size; j++)
        delete Cells[i][j];
}

// --------------------------------------------------------------------
bool Board::Is_Final_Position (
                QPoint last_added_coord,
                quint16 required_chain)
{
    qDebug() << "Is_Final_Position" << qPrintable(Point_Coord_To_Str(last_added_coord));

    // 4 directions till free or another owner cell.

    quint16 x=last_added_coord.x();
    quint16 y=last_added_coord.y();

    quint16 sum;
    int owner = Cells[x][y]->Get_Owner();
    int i, j;

    // ---- horizontal chain
    QVector<QPoint> Final_Chain;
    //Final_Chain.resize(board_size);

    Final_Chain.clear();

    Final_Chain.append(QPoint(x, y));
    sum = 1;
    i = last_added_coord.x()+1;
    j = last_added_coord.y();
    while (i<board_size &&
           Cells[i][j]->Is_Occupied() &&
           Cells[i][j]->Get_Owner()==owner) {
        Final_Chain.append(QPoint(i,j));
        sum++; i++;
    }

    i = last_added_coord.x()-1;
    while (i>=0 &&
           Cells[i][j]->Is_Occupied() &&
           Cells[i][j]->Get_Owner()==owner) {
        Final_Chain.append(QPoint(i,j));
        sum++; i--;
    }
    if (sum>=required_chain) {
        for (int c=0; c<Final_Chain.size(); c++) {
            quint16 x0 = Final_Chain.at(c).x();
            quint16 y0 = Final_Chain.at(c).y();
            Cells[x0][y0]->Set_Blink();
        }
        return true;
    }

    // --- vertical chain
    Final_Chain.clear();
    Final_Chain.append(QPoint(x,y));
    sum = 1;
    i = last_added_coord.x();
    j = last_added_coord.y()+1;
    while (j<board_size &&
           Cells[i][j]->Is_Occupied() &&
           Cells[i][j]->Get_Owner()==owner) {
        Final_Chain.append(QPoint(i,j));
        sum++; j++;
    }

    j = last_added_coord.y()-1;
    while (j>=0 &&
           Cells[i][j]->Is_Occupied() &&
           Cells[i][j]->Get_Owner()==owner) {
        Final_Chain.append(QPoint(i,j));
        sum++; j--;
    }
    if (sum>=required_chain) {
        for (int c=0; c<Final_Chain.size(); c++) {
            quint16 x0 = Final_Chain.at(c).x();
            quint16 y0 = Final_Chain.at(c).y();
            Cells[x0][y0]->Set_Blink();
        }
        return true;
    }
    return false;
}

// --------------------------------------------------------------------
void Board::Reset (void) {
    qDebug() << "Board::Reset";
    for (quint16 i=0; i<board_size; i++)
    for (quint16 j=0; j<board_size; j++) {
        Cell_Set_Possible_Move (i, j, false);
        if (Cell_Is_Occupied(i, j)) {
            int rc = Free_Cell(i, j);
            if (rc) {
                qCritical() << "Free cell" << Coord_To_Str(i, j) << "failed, rc=" << rc;
            }
        }
    }

}

#ifndef min
    #define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

// --------------------------------------------------------------------
void Board::Possible_Moves_update (const quint16 col, const quint16 row)
{
    quint16 col_min = (col < range_for_move ? 0 : col-range_for_move+1);
    quint16 col_max =  min (board_size, col + range_for_move);
    quint16 row_min = (row < range_for_move ? 0 : row-range_for_move+1);
    quint16 row_max =  min (board_size,  row + range_for_move);

    for (quint16 i=col_min; i<col_max; i++)
    for (quint16 j=row_min; j<row_max; j++) {
        if (! Cell_Is_Occupied(i, j))
            Cell_Set_Possible_Move (i, j, true);
    }
    Cell_Set_Possible_Move (col, row, false);
}

// --------------------------------------------------------------------
void Board::Possible_Moves_print (void) {
    qDebug() << "Possible moves:";
    for (quint16 j=0; j<board_size; j++) {
        QString s ("");
        for (quint16 i=0; i<board_size; i++) {
            if (Cell_Is_Occupied(i, j))
                s.append (" o");
            else
            s.append (Cell_Get_Possible_Move (i, j) ? " +" : " x");
        }
        qDebug() << s;
    }
}

// --------------------------------------------------------------------
int Board::Occupy_Cell (quint16 col, quint16 row, bool owner)
{
    qDebug() << "Occupy_Cell" << qPrintable(Coord_To_Str(col, row)) << ", owner=" << owner;
    if (col>=board_size || row>=board_size) {
        qCritical() << "Occupy_Cell: invalid coordinates" << qPrintable(Coord_To_Str(col, row));
        return -1;
    }
    if (Cell_Is_Occupied(col, row)) {
        qCritical() << "Cell" << qPrintable(Coord_To_Str(col, row)) << " is already occupied";
        return -2;
    }

    Cells[col][row]->Occupy(owner,
                            owner ? chip1_shape : chip0_shape,
                            owner ? chip1_color : chip0_color,
                            row, col);
    return 0;
}

// --------------------------------------------------------------------
int Board::Free_Cell (quint16 col, quint16 row) {
    qDebug() << "Free_Cell" << qPrintable(Coord_To_Str(col, row));
    if (col>=board_size || row>=board_size) {
        qCritical() << "Free_Cell: invalid coordinates" << qPrintable(Coord_To_Str(col, row));
        return -1;
    }
    if (! Cell_Is_Occupied(col, row)) {
        qCritical() << "Cell" << qPrintable(Coord_To_Str(col, row)) << " is already free";
        return -2;
    }

    Cells[col][row]->Free();
    return 0;
}

// --------------------------------------------------------------------
int Board::Cell_Is_Occupied (quint16 col, quint16 row) {
    //qDebug("Cell_Is_Occupied" << qPrintable(Coord_To_Str(col, row));
    Cell* pCell = NULL;
    int rc = Access_To_Cell(col, row, &pCell);
    if (rc) {
        qCritical() << "Cell_Is_Occupied: cannot access to cell" <<
                       qPrintable(Coord_To_Str(col, row));
        return 0;
    }
    else
        return pCell->Is_Occupied();
}

// --------------------------------------------------------------------
int  Board::Cell_Get_Possible_Move (quint16 col, quint16 row)
{
    Cell* pCell=NULL;
    int rc = Access_To_Cell(col, row, &pCell);
    if (rc) {
        qCritical() <<
                    "Cell_Get_Possible_Move: Cannot access to cell " <<
                    qPrintable(Coord_To_Str(col, row));
        return 0;
    }
    else {
        return pCell->Get_Possible_Move ();
    }
}

// --------------------------------------------------------------------
int Board::Cell_Set_Possible_Move (quint16 col, quint16 row, bool value) {
    //qDebug() << "Cell_Set_Possible_Move" << qPrintable(Coord_To_Str(col, row)) << "value=" << value;
    int result;
    Cell* pCell=NULL;
    int rc = Access_To_Cell(col, row, &pCell);
    if (rc) {
        qCritical() <<
                   "Cell_Set_Possible_Move: Cannot access to cell" <<
                   qPrintable(Coord_To_Str(col, row));
        result = -1;
    }
    else {
        pCell->Set_Possible_Move(value);
        result = 0;
    }
    return result;
}

// --------------------------------------------------------------------
int Board::Cell_Get_Owner (quint16 col, quint16 row) {
    int result;
    Cell* pCell=NULL;
    int rc = Access_To_Cell(col, row, &pCell);
    if (rc) {
        qCritical() << "Cell_Get_Owner: cannot access to cell" <<
                       qPrintable(Coord_To_Str(col, row));
        result = 0;
    }
    else
        result = pCell->Get_Owner();
    qDebug() << "Cell_Get_Owner =" << qPrintable(Coord_To_Str(col, row)) << " = " << result;
    return result;
}

// --------------------------------------------------------------------
int Board::Set_Chip_View  (bool owner, SHAPE_KIND shape, QColor color) {
    qDebug() << "Set_Chip_View owner=" << owner << "shape=" << Shape_Kind_To_Str(shape);
    if (owner) {
        chip1_shape = shape;
        chip1_color = color;
    }
    else {
        chip0_shape = shape;
        chip0_color = color;
    }
    return 0;
}

// --------------------------------------------------------------------
int Board::Access_To_Cell (quint16 col, quint16 row, Cell** pCell)
{
    if (col>=board_size || row>=board_size) {
        qCritical() << "Access_To_Cell: invalid coordinates" <<
                       qPrintable(Coord_To_Str(col, row));
        return -1;
    }
    *pCell = Cells[col][row];
    return 0;
}

// --------------------------------------------------------------------

