// ------------------------------------------------------
// game.h
// ------------------------------------------------------

#ifndef GAME_H
#define GAME_H

// ------------------------------------------------------
#include <QPoint>
#include <QTime>
#include <QWidget>

#include "const_int.h"
#include "types_int.h"
#include "configuration_typedef.h"

// ------------------------------------------------------
class Game : public QWidget
{

public:
    Game (CONFIGURATION_USERDEF& Configuration_Data,
          QWidget* pParent);
    ~Game();

public:
    static const QColor winner_color;
    static const QColor loser_color;
    static const QColor draw_color;
    static const QColor default_bg_color;

public:
    void    History_add          (const QPoint& point);
    int     History_remove_last  (void);
    void    History_reset        (void);
    void    History_print        (void);
    int     History_get_size     (void);

    void    Best_Estimated_print        (void);
    int     Best_Estimated_add          (QPoint point);
    void    Best_Estimated_reset        (void);
    QPoint  Best_Estimated_get_random   (void);

    quint16 Best_Estimated_Score_get    (void);
    void    Best_Estimated_Score_set    (quint16 value);

    QPoint  Current_Estimated_get    (void);
    void    Current_Estimated_set    (QPoint value);

    int     Possible_Moves_size  (void);
    void    Possible_Moves_print (void);
    void    Possible_Moves_reset (void);
    QPoint  Possible_Moves_get   (int i);
    int     Possible_Moves_add   (QPoint point);

    qint16  compare_cells_score (QPoint& cell0, QPoint& cell1);
    quint16 Get_Score (QPoint& cell);
    WINNER  Winner_get (void);
    void    Winner_set (WINNER value);

    int     SecsFromLastMove (void);
private:
    QTime           Last_Move_Time;
    QVector<HISTORY_ENTRY> History;
    QVector<QPoint> Possible_Moves;

    QPoint          Current_Estimated;

    QVector<QPoint> Best_Estimated;
    quint16         Best_Estimated_Score;

    WINNER          Winner;
};

#endif // GAME_H
