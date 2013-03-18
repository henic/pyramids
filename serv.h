// --------------------------------------------------------------------
// serv.h
// --------------------------------------------------------------------

#ifndef SERV_H
#define SERV_H

#include <QColor>
#include <QString>

#include "types_int.h"

QString Shape_Kind_To_Str   (SHAPE_KIND shape);
QColor  Random_Color        (void); // not really in use
QString Point_Coord_To_Str  (const QPoint& point);
QString Coord_To_Str        (const quint16 x, const quint16 y);

#endif // SERV_H
