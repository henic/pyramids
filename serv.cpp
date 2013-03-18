// --------------------------------------------------------------------
// serv.cpp
// --------------------------------------------------------------------

#include "serv.h"

// --------------------------------------------------------------------
QString Shape_Kind_To_Str (SHAPE_KIND shape)
{
    switch (shape) {
        case SHAPE_UNDEFINED:   return QString ("Undefined");
        case SHAPE_ROUND:       return QString ("Round");
        case SHAPE_SQUARE:      return QString ("Square");
        case SHAPE_TRIANGLE:    return QString ("Triangle");
        case SHAPE_XO:          return QString ("X-O");
        default:                return QString ("Unexpected " +
                                                QString::number(shape));
    }
}

// --------------------------------------------------------------------
QColor Random_Color (void)
{
    quint16 high = 255;
    quint16 r = (qrand() % (high + 1)),
            g = (qrand() % (high + 1)),
            b = (qrand() % (high + 1));
    return QColor (r, g, b);
}

// --------------------------------------------------------------------
QString Point_Coord_To_Str  (const QPoint& point)
{
    return "(" + QString::number(point.x()) + ":" + QString::number(point.y()) + ")";
}

// --------------------------------------------------------------------
QString Coord_To_Str  (const quint16 x, const quint16 y)
{
    return "(" + QString::number(x) + ":" + QString::number(y) + ")";
}

