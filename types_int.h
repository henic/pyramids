// --------------------------------------------------------------------
// types_int.h
// --------------------------------------------------------------------

#ifndef TYPES_INT_H
#define TYPES_INT_H

#include <QPoint>
#include <QTime>

typedef enum {
    SHAPE_UNDEFINED=0,
    SHAPE_ROUND,
    SHAPE_SQUARE,
    SHAPE_TRIANGLE,
    SHAPE_XO
} SHAPE_KIND;

typedef struct {
    QPoint point;
    QTime  move_time;
} HISTORY_ENTRY;

typedef enum {
    Winner_0 = 0,
    Winner_1,
    Winner_Draw,
    Winner_Undefined
} WINNER;

#define KEY_UNKNOWN             0
#define KEY_ESTIMATION_DONE     1
#define KEY_REST_TIME           2
//#define KEY_

const unsigned int LINE_LEN=128;
typedef char LINE[LINE_LEN];

#endif // TYPES_INT_H
