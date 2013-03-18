// ------------------------------------------------------
// estimation.cpp
// ------------------------------------------------------

// todo list:
//
// run this thread only in computer mode (not sure, "treat", "tip")
// variables to use: best_estimated, current_estimated, possible_moves, status

#include <QDebug>

#include "board.h"
#include "configuration.h"
#include "estimation.h"
#include "game.h"
#include "serv.h"

// --------------------------------------------------------------------
Estimation_Thread::Estimation_Thread(
        Board* board, Game* game,
        CONFIGURATION_USERDEF* pConfiguration,
        QObject *parent) :
    QThread(parent)
{
    qDebug() << "Estimation constructor";
    stopped = false;
    m_board = board;
    m_game  = game;
    m_Configuration = pConfiguration;
}

// --------------------------------------------------------------------
void Estimation_Thread::stop(void)
{
    stopped_mutex.lock();
    stopped = true;
    stopped_mutex.unlock();
}

// --------------------------------------------------------------------
void Estimation_Thread::stop_and_wait (void)
{
    if (this->isRunning()) {
        this->stop ();
        this->wait (2000);
    }
}

// --------------------------------------------------------------------
bool Estimation_Thread::Check_Flag_Stopped (void)
{
    bool result = false;
    stopped_mutex.lock();
    if (stopped) {
        stopped = false;
        result = true;
    }
    stopped_mutex.unlock();
    return result;
}

// --------------------------------------------------------------------
void Estimation_Thread::Create_Possible_Moves_List (quint16 board_size)
{

    m_game->Possible_Moves_reset();

    for (quint16 i=0; i<board_size; i++)
    for (quint16 j=0; j<board_size; j++) {
        if (! m_board->Cell_Is_Occupied(i,j)) {
            m_game->Possible_Moves_add(QPoint(i, j));
        }
    }
    //m_game->Possible_Moves_print();
}

// --------------------------------------------------------------------
void Estimation_Thread::Estimate_Move (int i, quint16& best_score)
{
    QPoint current_estimated = m_game->Possible_Moves_get(i);
    qDebug() << "===== Estimation" << qPrintable(Point_Coord_To_Str(current_estimated)) << "=====";
    m_game->Current_Estimated_set(current_estimated); // locker
    quint16 current_score = m_game->Get_Score(current_estimated);
    qDebug()<<"Score = " << current_score;

    // well, this function is more complicated
    if (best_score < current_score) {
        best_score = current_score;
        m_game->Best_Estimated_reset();
        m_game->Best_Estimated_Score_set(best_score);
    }
    if (best_score == current_score) { // <= really
        m_game->Best_Estimated_add(current_estimated); // locker?
    }

    QThread::msleep(300); // to show
}

// --------------------------------------------------------------------
void Estimation_Thread::run()
{
    qDebug() << "Estimation_Thread::run";
    // create possible_moves list
    quint16 board_size = m_Configuration->Board_Size;
    Create_Possible_Moves_List (board_size);
    bool exit_flag = false;
    while (!exit_flag) {

        if (Check_Flag_Stopped())
            break;

        quint16 best_score = 0;
        int possible_moves_number = m_game->Possible_Moves_size();

        for (int i=0; i<possible_moves_number; i++)
        {
            Estimate_Move(i, best_score);

            // update rest_time
            int secs_from_last_move = m_game->SecsFromLastMove();
            if (i>0 && secs_from_last_move>0) { // no relevant info before
                int Rest_time =
                        secs_from_last_move*(possible_moves_number - i) / i;
                qDebug() <<"Rest time=" << Rest_time;
                emit (Estimation_Thread_Signal_Int(KEY_REST_TIME, Rest_time)); // add var; locker
            }

            if (Check_Flag_Stopped())
                break;
        }

        exit_flag = true; // remove cycle
    }
    qDebug()<<"Emit estimation finished";
    emit (Estimation_Thread_Signal_Int(KEY_ESTIMATION_DONE, 0));
}

