// --------------------------------------------------------------------
// mainwindow.h
// --------------------------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

#include "const_int.h"
#include "types_int.h"
#include "configuration_typedef.h"
#include "estimation.h"
#include "game.h"
#include "pushbutton_chip.h"

QString& Get_Debug_File_Name (void);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget* pParent = 0, Qt::WindowFlags Flag = Qt::Window);
    ~MainWindow();

public:
    static const QColor default_bg_color;

private slots:
    void on_pushButton_Quit_clicked();
    void on_pushButton_Move_Now_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Start_clicked();
    void on_pushButton_Takeback_clicked();
    void on_pushButton_Options_clicked();

    void onSave();
    void onLoad();
    void onAbout();
    void onAuthor();

    void onTimer_Move_Expired ();
    void onTimer_Tip_Expired ();
    void onTimer_Threat_Expired ();
    void onTimer_Update_Data_Expired();
    void onTimer_TimeSlot(void);
    void keyPressEvent  (QKeyEvent *keyevent);
    void paintEvent     (QPaintEvent *event);
    void mousePressEvent(QMouseEvent* pMouseEvent);

    void Slot_Clicked_Cell (int col, int row);
    void Slot_Update_Dynamical_Data (int,int);

    void on_pushButton_View_Log_clicked();

private:
    void Init_GUI_Menu          (void);
    void Init_Chips             (void);
    void Init_Internal_Data     (void);
    void Init_Status_Bar        (void);
    void Init_Board             (void);
    void Init_Timers            (void);
    void Stop_Timers            (void);
    void Connect_Cells          (void);
    void Disconnect_Cells       (void);
    void Draw_Move_Sign         (QPainter& painter, bool side);
    void Draw_Winner_Side       (QPainter& painter);
    void Draw_Text              (QPainter& painter, QString& Text);

    void Update_Status          (const QString& Text);
    void Update_Estimated       (const QPoint& point);
    void Update_Best_Estimated  (const QPoint& point, quint16 score);
    void Update_Expected_Rest_Time (const int Sec);
    void Update_Rest_Time       (const int Sec);

    int  Active_Side_Is_Computer (void);
    int  Make_Move (quint16 i, quint16 j);
    void Compute_Geometry_For_Board (QRect& Rect);
    void Clear_Data (void);
    void PreMove_Action (void);
    int  Access_To_Cell (quint16 col, quint16 row, Cell** pCell);
    void Update_Chips_Quantity (void);
    int  Check_Final_Position(quint16 i, quint16 j);
    QString Game_Result_To_Str (WINNER game_result);
    void Stop_Threads (void);

private:
    Ui::MainWindow *ui;

    CONFIGURATION_USERDEF Configuration_Data;

    bool Game_Is_Active;
    bool Active_Side;
    bool Draw_Move_Sign_Flag;
    bool Press_To_Reset;

    QTimer *Timer_Move;
    QTimer *Timer_Tip;
    QTimer *Timer_Threat;

    QTimer *Timer_Update_Data;

    QTimer* Timer_Status;
    QLabel* DateTimeLabel;
    QLabel* MovesLabel;

    pushbutton_chip *Chip_0, *Chip_1;

    QRect   Board_Rect;
    Board*  board;
    Game*   game;
    Estimation_Thread* estimation_thread;
};

#endif // MAINWINDOW_H
