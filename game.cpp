// --------------------------------------------------------------------
// game.cpp
// --------------------------------------------------------------------

#include <QDebug>

#include "configuration_typedef.h"
#include "game.h"
#include "serv.h"

Game::Game(CONFIGURATION_USERDEF& Configuration_Data,
           QWidget* pParent)
        : QWidget(pParent)
{
    qDebug() << "Game constructor";
    Current_Estimated = QPoint (0,0);
    Best_Estimated.resize(Configuration_Data.Board_Size);
    Best_Estimated_reset();
    Winner_set(Winner_Undefined);
    Possible_Moves_reset();
    Last_Move_Time = QTime::currentTime();
}

Game::~Game()
{

}

// --------------------------------------------------------------------
const QColor Game::winner_color     = QColor (152,251,152); //pale green
const QColor Game::loser_color      = QColor (255,182,193); // light pink
const QColor Game::draw_color       = QColor (176,196,222); // light steel blue
const QColor Game::default_bg_color = QColor (221,221,221);

// --------------------------------------------------------------------
WINNER  Game::Winner_get (void)         {return Winner;}
void    Game::Winner_set (WINNER value) {Winner = value;}

// --------------------------------------------------------------------
quint16 Game::Get_Score (QPoint& cell)
{
    qDebug() << "Get_Score" << qPrintable(Point_Coord_To_Str(cell));
    return 10; //rand () % 20;
}

// --------------------------------------------------------------------
qint16 Game::compare_cells_score (
                QPoint& cell0,
                QPoint& cell1)
{
    qDebug() << "compare_cell_scores" <<
                qPrintable(Point_Coord_To_Str(cell0)) << "-" <<
                qPrintable(Point_Coord_To_Str(cell1));
    return (rand()%3) -1; // -1, 0, 1
}

// --------------------------------------------------------------------
void Game::Best_Estimated_print (void)
{
    qDebug() << "Best_Estimated: score = " << Best_Estimated_Score;
    int size = Best_Estimated.size();
    for (int i=0; i<size; i++)
        qDebug("%02d. %s", i, qPrintable(Point_Coord_To_Str(Best_Estimated[i])));
}

// --------------------------------------------------------------------
int Game::Best_Estimated_add (QPoint point) {
    // check validity?
    Best_Estimated.append (point);
    return 0;
}

// --------------------------------------------------------------------
void Game::Best_Estimated_reset (void) {
    qDebug()<<"Best_Estimated_reset";
    Best_Estimated.clear();
    Best_Estimated_Score = 0;
}

// --------------------------------------------------------------------
QPoint Game::Best_Estimated_get_random(void) {
    int size = Best_Estimated.size();
    if (size==0) {
        qCritical() << "Best_Estimated_get_random, unexpected empty array";
        return QPoint(0,0);
    }
    else
        return Best_Estimated.at(rand() % size);
}

// --------------------------------------------------------------------
quint16 Game::Best_Estimated_Score_get    (void) {return Best_Estimated_Score;}
void    Game::Best_Estimated_Score_set    (quint16 value) {Best_Estimated_Score = value;}

QPoint  Game::Current_Estimated_get       (void) {return Current_Estimated;}
void    Game::Current_Estimated_set       (QPoint value) {Current_Estimated = value;}

// --------------------------------------------------------------------
void Game::History_print (void)
{
    qDebug() << "History: ";
    int size = History.size();

    for (int i=0; i<size; i++) {
        HISTORY_ENTRY* pHistory = &History[i];
        qDebug("%02d. %s, time=%s",
               i, qPrintable(Point_Coord_To_Str(pHistory->point)),
               qPrintable (pHistory->move_time.toString("h:m:s")));
    }
}

// --------------------------------------------------------------------
int Game::SecsFromLastMove (void) {
    QTime current_time = QTime::currentTime();
    return Last_Move_Time.secsTo(current_time);
}

// --------------------------------------------------------------------
void Game::History_add (const QPoint& coord)
{
    Last_Move_Time = QTime::currentTime();
    QString timeString = Last_Move_Time.toString("hh:mm:ss");
    qDebug ("History_add %s, time=%s",
            qPrintable(Point_Coord_To_Str(coord)),
            qPrintable(timeString));
    int size = History.size();
    if (size<0) {
        qCritical() << "Unexpected empty History array";
    }
    else {
        HISTORY_ENTRY history_entry = {coord, Last_Move_Time};
        History.append(history_entry);
        History_print ();
    }
}

// --------------------------------------------------------------------
void Game::History_reset (void) {
    History.clear();
}

// --------------------------------------------------------------------
int Game::History_remove_last(void)
{
    qDebug() << "History_remove_last";
    int size = History.size();
    if (size<=0) {
        qCritical() << "Unexpected empty History array";
        return -1;
    }
    else {
        History.remove(size-1);
        return 0;
    }
}

// --------------------------------------------------------------------
int Game::History_get_size (void) {
    return History.size();
}

// --------------------------------------------------------------------
void Game::Possible_Moves_reset (void) {
    Possible_Moves.clear();
}

// --------------------------------------------------------------------
int Game::Possible_Moves_size(void) { return Possible_Moves.size();}

// --------------------------------------------------------------------
void Game::Possible_Moves_print (void)
{
    qDebug() << "Possibe_Moves:";
    int size = Possible_Moves_size();

    for (int i=0; i<size; i++)
        qDebug("%02d. %s",
               i, qPrintable(Point_Coord_To_Str(Possible_Moves[i])));
}

// --------------------------------------------------------------------
int Game::Possible_Moves_add (QPoint point) {
    // check validity?

    Possible_Moves.append (point);
    return 0;
}

// --------------------------------------------------------------------
QPoint Game::Possible_Moves_get(int i) {
    int size = Possible_Moves_size();
    if (i<0 || i>=size) {
        qCritical() << "Possibe_Moves_get: invalid index " << i;
        return QPoint(0,0);
    }
    else
        return Possible_Moves.at(i);
}

// --------------------------------------------------------------------
/*
int Game::Possible_Moves_update (QPoint coord) {
    //qDebug("Possible_Moves_update" <<
        qPrintable(Point_Coord_To_Str(coord));
    Possible_Moves_add (coord);
    return 0;
}
*/

