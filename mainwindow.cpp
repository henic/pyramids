// --------------------------------------------------------------------
// mainwindow.cpp
// --------------------------------------------------------------------

#include <QBrush>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QTextEdit>

#include "const_int.h"
#include "configuration.h"
#include "estimation.h"
#include "mainwindow.h"
#include "options.h"
#include "serv.h"
#include "ui_mainwindow.h"

#include "chkheap.h"

// -------------------------------------------------
const QColor MainWindow::default_bg_color = QColor (212,208,200);

// -------------------------------------------------
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags Flag) :
    QMainWindow(parent, Flag),
    ui(new Ui::MainWindow)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    ///qDebug () << applicationName(); !!!

    Configuration_Load (Configuration_Data, Default_Ini_File_Name, true);

    setWindowTitle("Pyramids");
    setWindowIcon(QIcon(":/icons/pyramids.png"));
    ui->setupUi(this);

    Timer_Move = Timer_Tip = Timer_Threat = Timer_Status = NULL;
    Init_GUI_Menu ();
    Init_Internal_Data();
    Init_Timers ();
    Init_Status_Bar();

    Init_Board ();
}


// -------------------------------------------------
void MainWindow::Init_Board ()
{
    // to be initialized later, after "Start" press
    game = NULL;
    estimation_thread = NULL;

    Compute_Geometry_For_Board (Board_Rect);
    board = new Board (Configuration_Data, Board_Rect, this);
    Init_Chips ();
    Connect_Cells ();
}

// -------------------------------------------------
// init modules
// -------------------------------------------------
MainWindow::~MainWindow()
{
    Stop_Threads();
    if (Timer_Move!=NULL) { //remove
    delete Timer_Move;
    delete Timer_Tip;
    delete Timer_Threat;
    delete Timer_Update_Data;

    delete DateTimeLabel;
    delete Timer_Status;
    delete MovesLabel;
    }
    if (board != NULL) {
        delete board;
        board = NULL;
    }
    if (game != NULL) {
        delete game;
        game = NULL;
    }
    if (estimation_thread!=NULL) {
        estimation_thread->stop_and_wait();
        delete estimation_thread;
        estimation_thread = NULL;
    }

    if (Chip_0 != NULL) {
        delete Chip_0;
        Chip_0 = NULL;
    }
    if (Chip_1 != NULL) {
        delete Chip_1;
        Chip_1 = NULL;
    }

    delete ui;
#if CHKHEAP_MODULE==1
    CHKHEAP();
#endif

}

// -------------------------------------------------
void MainWindow::Init_Internal_Data (void)
{
    qDebug() << "Init_Internal_Data";
    Draw_Move_Sign_Flag = false;
    Press_To_Reset      = false;
    Game_Is_Active      = false;
    Active_Side         = 0; // first (left) player

    Chip_0              = NULL;
    Chip_1              = NULL;
}

// -------------------------------------------------
void MainWindow::Connect_Cells (void)
{

    for (quint16 i=0; i<Configuration_Data.Board_Size; i++)
    for (quint16 j=0; j<Configuration_Data.Board_Size; j++) {
        Cell* pCell;
        int rc = Access_To_Cell(i, j, &pCell);
        if (rc) {
            qCritical() << "MainWindow::Connect_Cells: Cannot access to cell" <<
                           qPrintable(Coord_To_Str(i, j));
        return;
        }
        else
            connect (pCell, SIGNAL(clicked(int, int)),
                     this,  SLOT(Slot_Clicked_Cell(int, int)));
    }
}

// -------------------------------------------------
void MainWindow::Disconnect_Cells (void)
{

    for (quint16 i=0; i<Configuration_Data.Board_Size; i++)
    for (quint16 j=0; j<Configuration_Data.Board_Size; j++) {
        Cell* pCell;
        int rc = Access_To_Cell(i, j, &pCell);
        if (rc) {
            qCritical() << "MainWindow::Disconnect_Cells: Cannot access to cell" <<
                           qPrintable(Coord_To_Str(i, j));
        return;
        }
        else
            disconnect (pCell, SIGNAL(clicked(int, int)),
                     this,  SLOT(Slot_Clicked_Cell(int, int)));
    }
}

// -------------------------------------------------
void MainWindow::Init_Timers (void) {
    qDebug() << "Init_Timers";

    Timer_Move = new QTimer (this);
    Timer_Move->setSingleShot(true);
    connect(Timer_Move, SIGNAL(timeout()), this,
            SLOT(onTimer_Move_Expired()));

    Timer_Tip = new QTimer (this);
    Timer_Tip->setSingleShot(true);
    connect(Timer_Tip, SIGNAL(timeout()), this,
            SLOT(onTimer_Tip_Expired()));

    Timer_Threat= new QTimer (this);
    Timer_Threat->setSingleShot(true);
    connect(Timer_Threat, SIGNAL(timeout()), this,
            SLOT(onTimer_Threat_Expired()));

    Timer_Update_Data = new QTimer (this);
    connect(Timer_Update_Data, SIGNAL(timeout()), this,
            SLOT(onTimer_Update_Data_Expired()));
}


// -------------------------------------------------
void MainWindow::onSave(void)
{
    QMessageBox::information(0,
                     "Qt Application Example",
                     "Qt Application Example" );
    Update_Status ("onSave");
}

// -------------------------------------------------
void MainWindow::onLoad(void)
{
    Update_Status("onLoad");

}

// -------------------------------------------------
void MainWindow::onAbout(void)
{
    QMessageBox::aboutQt (this, "Qt Application Example");
}

// -------------------------------------------------
void MainWindow::onAuthor(void)
{
    QMessageBox::aboutQt (this, "Qt Application Example");
}


// -------------------------------------------------
void MainWindow::on_pushButton_Options_clicked()
{
    qDebug() << "Options clicked";

    Options Configuration_Dialog (&Configuration_Data, Game_Is_Active);
    int retCode = Configuration_Dialog.exec();
    if ( retCode==QDialog::Accepted ) {
        //  store possible changes
        // update also local members
        Configuration_Data = *Configuration_Dialog.Get_Updated_Configuration();
        Configuration_Save(Configuration_Data, Default_Ini_File_Name);

        Chip_0->Chip_Set (Configuration_Data.Chip0_Shape,
                          Configuration_Data.Chip0_Color);
        Chip_1->Chip_Set (Configuration_Data.Chip1_Shape,
                          Configuration_Data.Chip1_Color);
        if (board!=NULL) {

            // ------------------------------------------------------------
            // reallocate/redraw board in case that desk size was changed.
            // ------------------------------------------------------------
            Disconnect_Cells ();
            Init_Board();
            // ------------------------------------------------------------

            board->Set_Chip_View(false,
                                 Configuration_Data.Chip0_Shape,
                                 Configuration_Data.Chip0_Color);
            board->Set_Chip_View(true,
                                 Configuration_Data.Chip1_Shape,
                                 Configuration_Data.Chip1_Color);
        }
        update ();

    } else
    if ( retCode==QDialog::Rejected ) {
        // discard possible changes - use defaults
    } else {
        // when Delete is pressed, i would like to jump here
        // use defaults?
    }
}

// -------------------------------------------------
void MainWindow::Stop_Timers (void)
{
    if (Active_Side_Is_Computer()) {
        if (Timer_Move!=NULL)
            Timer_Move->stop();
    }
    else { // stop timers used for human
        if (Configuration_Data.Show_Tip)
            if (Timer_Tip!=NULL)
                Timer_Tip->stop();
        if (Configuration_Data.Show_Threat)
            if (Timer_Threat!=NULL)
                Timer_Threat->stop();
    }
    Timer_Update_Data->stop();
}

// -------------------------------------------------
//  keyboard events
// -------------------------------------------------
void MainWindow::keyPressEvent (QKeyEvent *event)
{
    const int ScrollStep = 10;
    switch (event->key()) {
    case Qt::Key_Escape:
        Update_Status("You pressed ESC");
        break;

    case Qt::Key_Enter:
        Update_Status("You pressed Enter");
        break;

    case Qt::Key_Return:
        Update_Status("You pressed Return");
        break;

    case Qt::Key_Left:
        Update_Status("You pressed Left");
        scroll(-ScrollStep, 0);
        break;

    case Qt::Key_Right:
        Update_Status("You pressed Right");
        scroll(+ScrollStep, 0);
        break;

    case Qt::Key_Up:
        Update_Status("You pressed Up");
        scroll(0, +ScrollStep);
        break;

    case Qt::Key_Down:
        Update_Status("You pressed Down");
        scroll(0, -ScrollStep);
        break;

    case Qt::Key_F1:
        Update_Status("You pressed F1");
        break;

    default:
        QMainWindow::keyPressEvent (event);
    }

    /*
    if (Press_To_Reset) {
        emit (on_pushButton_Stop_clicked());
        Press_To_Reset = false;
    }
    */
}



// -------------------------------------------------
// pushbutton events
// -------------------------------------------------
int  MainWindow::Active_Side_Is_Computer (void) {
    return (Active_Side ?
                Configuration_Data.Second_Is_Computer :
                Configuration_Data.First_Is_Computer);
}

// -------------------------------------------------
void MainWindow::Stop_Threads (void)
{
    // to be added stop_tip_thread and stop_threat_thread
    if (estimation_thread != NULL) {
        estimation_thread->stop_and_wait();
        delete estimation_thread;
        estimation_thread = NULL;
    }
}

// -------------------------------------------------
void MainWindow::on_pushButton_Quit_clicked()
{
    emit (on_pushButton_Stop_clicked());
    Clear_Data();
    close ();
}

// -------------------------------------------------
void MainWindow::on_pushButton_Move_Now_clicked()
{
    Update_Status("Move now pressed");
    emit (onTimer_Move_Expired());
}

// -------------------------------------------------
void MainWindow::Clear_Data (void)
{
    qDebug () << "MainWindow::Clear_Data";
    board->Reset();

    if (game != NULL) {
        game->History_reset();
        game->Best_Estimated_reset();
    }
}

// -------------------------------------------------
void MainWindow::on_pushButton_Stop_clicked()
{
    Game_Is_Active = false;

    ui->pushButton_Start->setEnabled (true);
    ui->pushButton_Stop-> setEnabled (false);

    ui->pushButton_Move_Now->setEnabled(false);
    ui->pushButton_Takeback->setEnabled(false);

    Draw_Move_Sign_Flag = false;

    Stop_Timers ();
    Stop_Threads ();
}

// -------------------------------------------------
void MainWindow::on_pushButton_Start_clicked()
{
    game = new Game (Configuration_Data, this);

    Press_To_Reset = false;
    Game_Is_Active = true;

    ui->pushButton_Start->setEnabled (false);
    ui->pushButton_Stop-> setEnabled (true);

    // if both are computers, disable takeback button
    if (Configuration_Data.First_Is_Computer &&
        Configuration_Data.Second_Is_Computer)
        ui->pushButton_Takeback->setEnabled(false);

    Draw_Move_Sign_Flag = true;  // highlight active side

    Clear_Data ();

    Active_Side = false; // 0, first player
    PreMove_Action (); // contains bg run

    update ();
}


// -------------------------------------------------
void MainWindow::PreMove_Action (void) 
{
    if (! Game_Is_Active)
        return;
    qDebug() << "PreMove_Action";
    // pre-move: start timers, enable movenow button, run thinking

    Timer_Update_Data->start(1000); // 1 second

    if (Active_Side_Is_Computer()) {
        ui->pushButton_Move_Now->setEnabled(true);
        if (Configuration_Data.Limit_Move_Time)
            Timer_Move->start(Configuration_Data.Limit_Move_Time_Sec*1000);

        estimation_thread = new Estimation_Thread (board, game, &Configuration_Data);
        estimation_thread->start();

        connect(estimation_thread,
                SIGNAL(Estimation_Thread_Signal_Int(int, int)),
                this, SLOT(Slot_Update_Dynamical_Data(int, int)));
    }
    else { // human
        ui->pushButton_Move_Now->setEnabled(false);
        if (Configuration_Data.Show_Threat)
            Timer_Threat->start(Configuration_Data.Delay_Show_Threat);

        if (Configuration_Data.Show_Tip)
            Timer_Tip->start(Configuration_Data.Delay_Show_Tip);
    }
}

// -------------------------------------------------
void MainWindow::on_pushButton_Takeback_clicked()
{
    qDebug() << "takeback pressed";
    // check is it possible to  takeback
    // remove from history, current_state, possible_moves,
    // update active_side;
    // repeat if active_is_computer
}

// -------------------------------------------------
// timer events
// -------------------------------------------------

// -------------------------------------------------
void MainWindow::onTimer_Tip_Expired (void) {
    qDebug() << "TimerTip expired";
    // blink best and its neighbours (skip if none)
}

// -------------------------------------------------
void MainWindow::onTimer_Threat_Expired (void) {
    qDebug() << "TimerThreat expired";
}

// -------------------------------------------------
void MainWindow::Slot_Update_Dynamical_Data (int key, int value)
{

    //qDebug() << "Slot_Update_Dynamical_Data" << key << value;
    switch (key) {
        case KEY_UNKNOWN:
            qDebug() << "Slot_Update_Dynamical_Data: Undefined key";
            qCritical() << "Undefined key";
            break;
        case KEY_ESTIMATION_DONE:
            qDebug() << "Slot_Update_Dynamical_Data: Estimation done";
            emit (onTimer_Move_Expired());
            break;
        case KEY_REST_TIME:
            qDebug() << "Slot_Update_Dynamical_Data: Rest_Time" << value;
            Update_Expected_Rest_Time(value);
            break;
        default:
            qCritical() << "Unknown key";
            break;
    }

    //Update_Status();
}

//------------------------------------------------------------
void MainWindow::onTimer_Update_Data_Expired()
{
    qDebug() << "Timer_Update_Data expired";
    if (game!=NULL) {

        Update_Best_Estimated(
                    game->Best_Estimated_get_random(),
                    game->Best_Estimated_Score_get());
        Update_Estimated(game->Current_Estimated_get());

        if (Configuration_Data.Limit_Move_Time)
        Update_Rest_Time( // hope timer will be expired at zero value
                    Configuration_Data.Limit_Move_Time_Sec -
                    game->SecsFromLastMove());
    }
}

//------------------------------------------------------------
void MainWindow::onTimer_TimeSlot()
{
    QDateTime Time = QDateTime::currentDateTime();
    DateTimeLabel->setText(Time.toString("dd.MM.yyyy - hh:mm:ss"));
}

// -------------------------------------------------
void MainWindow::onTimer_Move_Expired (void) {
    qDebug() << "TimerMove expired";
    if (! Active_Side_Is_Computer()) {
        qCritical() << "Timer should be off for computer";
        return;
    }

    if (estimation_thread != NULL) {
        if (! estimation_thread->isRunning()) {
            //qCritical() << "Estimation thread should be on"; //remove! check
            //return;
        }
        estimation_thread->stop_and_wait();
        delete estimation_thread;
        estimation_thread = NULL;
    }

    QPoint best_choice = game->Best_Estimated_get_random ();
    int rc = Make_Move (best_choice.x(), best_choice.y());
    if (rc) {
        qCritical() << "Make_Move" <<
                  qPrintable(Point_Coord_To_Str(best_choice)) <<
                  "returned " << rc;
        return;
    }
}

// -------------------------------------------------
void MainWindow::Update_Chips_Quantity (void) {
    QLabel* pChipsNumberLabel =
                Active_Side ?
                    ui->label_chips_number_1 :
                    ui->label_chips_number_0;
    QString strChipsNumber;
    strChipsNumber.sprintf(
                "%d (%d)",
                (game->History_get_size()+1) >> 1,
                Configuration_Data.Chips_Number);
    pChipsNumberLabel->setText(strChipsNumber);
}


// -------------------------------------------------
int MainWindow::Check_Final_Position(quint16 i, quint16 j)
{
    int result = 0;
    if (board->Is_Final_Position(QPoint(i, j),
                                 Configuration_Data.Chain_Length))
    {
        qDebug() << "Final position reached";
        game->Winner_set(Active_Side ? Winner_1 : Winner_0);
        result = 1;
    }
    else  //if no_more_chips)
    if (game->History_get_size() == Configuration_Data.Chips_Number<<1) {
        qDebug() << "No more chips";
        game->Winner_set(Winner_Draw);
        result = 1;
    }
    return result;
}

// -------------------------------------------------
// move realization
// -------------------------------------------------
int MainWindow::Make_Move(quint16 i, quint16 j)
{
    qDebug() << "========== Make_Move " << qPrintable(Coord_To_Str(i, j)) << "==========";

    Stop_Timers();

    //check validity
    if (board->Cell_Is_Occupied(i, j)) {
        qCritical() << "Make_Move: cell is occupied already";
        return -1;
    }
    QPoint coord (i, j);

    //draw new position of chip
    board->Occupy_Cell(coord.x(), coord.y(), Active_Side);
    board->Possible_Moves_update(i, j);
    board->Possible_Moves_print ();

    game->Best_Estimated_reset();
    game->History_add (coord);

    //update chips quantity
    Update_Chips_Quantity ();

    if (Check_Final_Position(i, j)) {
        Press_To_Reset = true;
        emit (on_pushButton_Stop_clicked());
        update ();
        return 0;
    }

    Active_Side = ! Active_Side;

    if (!Active_Side_Is_Computer())
        ui->pushButton_Takeback->setEnabled(true);

    PreMove_Action();
    update ();

    return 0;
}


// -------------------------------------------------
void MainWindow::Update_Estimated (const QPoint& point) {
    QString msg;
    msg.sprintf("Estimating: (%d:%d)", point.x(), point.y());
    ui->label_estimating_now->setText(msg);
}

// -------------------------------------------------
void MainWindow::Update_Expected_Rest_Time (const int Sec) {
    ui->label_expected_rest_time->setText(
                "Expected rest time: " + QString::number(Sec));
}

// -------------------------------------------------
void MainWindow::Update_Rest_Time (const int Sec) {
    qDebug()<<"Update_Rest_Time" << Sec;
    ui->label_rest_time->setText("Rest time: " + QString::number(Sec));
}

// -------------------------------------------------
void MainWindow::Update_Best_Estimated (const QPoint& point, quint16 score) {
    QString msg;
    msg.sprintf("Best: (%d:%d), score=%d",
                point.x(), point.y(), score);
    ui->label_best_estimated->setText(msg);
}

// -------------------------------------------------
void MainWindow::Update_Status (const QString& Text) {
    ui->Status->setText(Text);
}

// --------------------------------------------------------------------
int MainWindow::Access_To_Cell (quint16 col, quint16 row, Cell** pCell)
{
    return board->Access_To_Cell(col, row, pCell);
}

// --------------------------------------------------------------------
void MainWindow::Slot_Clicked_Cell (int col, int row)
{
    qDebug() << "MainWindow::Slot_Clicked_Cell" <<
                qPrintable(Coord_To_Str(col, row));

    if (Game_Is_Active && !Active_Side_Is_Computer())
        Make_Move(col, row);
}

// --------------------------------------------------------------------
void MainWindow::mousePressEvent(QMouseEvent* /*pMouseEvent*/)
{
    /*
    if (Press_To_Reset) {
        emit (on_pushButton_Stop_clicked());
        Press_To_Reset = false;
    }
    */
}


void MainWindow::on_pushButton_View_Log_clicked()
{
    qDebug()<<"View Logfile";

    QString filename = Get_Debug_File_Name();
    QString File_Content;

    if(filename.isEmpty()) // use default if no filename passed
        return;            // well it's unnecessary: next check contains it
    if (! QFile::exists(filename))
        return;




    QTextEdit* edit = new QTextEdit ();

    edit->setReadOnly(true);

    edit->setFixedSize(300,200);
    edit->setWindowTitle("View file");

    edit->setPlainText("This is my TEXT !!");

    QFont* font = new QFont("Courier new");
    font->setPixelSize(120);
    font->setBold(true);
    edit->setFont(*font);

    edit->show();
}
