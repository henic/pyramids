// --------------------------------------------------------------------
// configuration_typedef.h
// --------------------------------------------------------------------

#ifndef CONFIGURATION_TYPEDEF_H
#define CONFIGURATION_TYPEDEF_H

#include <QtGlobal>
#include <QColor>
#include "types_int.h"

typedef struct {

    quint16 Board_Size;
    quint16 Chips_Number;
    quint16 Chain_Length;

    bool    First_Is_Computer;
    quint16 First_Computer_Level;

    bool    Second_Is_Computer;
    quint16 Second_Computer_Level;

    bool    Show_Tip;
    quint16 Delay_Show_Tip;

    bool    Show_Threat;
    quint16 Delay_Show_Threat;

    bool    Limit_Move_Time;
    quint16 Limit_Move_Time_Sec;

    quint16 Delay_Betweeen_Computer_Moves;

    quint16 Comp_Search_Depth;
    quint16 Moves_Search_Range;

    bool    Skip_Confirmation;

    SHAPE_KIND Chip0_Shape;
    QColor     Chip0_Color; // not saved in cfg
    int Chip0_Color_r, Chip0_Color_g, Chip0_Color_b;

    SHAPE_KIND Chip1_Shape;
    QColor     Chip1_Color; // not saved in cfg
    int Chip1_Color_r, Chip1_Color_g, Chip1_Color_b;

    QString Player_0_Name;
    QString Player_1_Name;

} CONFIGURATION_USERDEF;

#endif // CONFIGURATION_TYPEDEF_H
