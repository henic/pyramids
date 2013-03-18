// ------------------------------------------------------
// estimation.h
// ------------------------------------------------------

#ifndef ESTIMATION_H
#define ESTIMATION_H

#include <QThread>
#include <QString>
#include <QMutex>

#include "const_int.h"
#include "board.h"
#include "game.h"

class Estimation_Thread : public QThread
{
    Q_OBJECT

public:
    //explicit
    Estimation_Thread (Board* board, Game* game, CONFIGURATION_USERDEF* pConfiguration,
                       QObject *parent = 0);
    void stop_and_wait (void);

signals:
    void Estimation_Thread_Signal(QString);
    void Estimation_Thread_Signal_Int(int, int);

private:
    void run();
    void stop();
    bool Check_Flag_Stopped (void);
    void Create_Possible_Moves_List (quint16 board_size);
    void Estimate_Move (int i, quint16& best_score);

private:
    volatile bool stopped;
    QMutex stopped_mutex;
    QString messageStr;

    Board* m_board;
    Game*  m_game;
    CONFIGURATION_USERDEF* m_Configuration;
};

#endif // ESTIMATION_H

// ------------------------------------------------------
