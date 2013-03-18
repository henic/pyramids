// --------------------------------------------------------------------
// mainwindow_draw.cpp
// --------------------------------------------------------------------

#include <QDebug>
#include <QPainter>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

// -------------------------------------------------
// compute geometry for Board
void MainWindow::Compute_Geometry_For_Board (QRect& Rect)
{
    QRect p0_geometry = ui->groupBox_player_0->geometry();
    QRect p1_geometry = ui->groupBox_player_1->geometry();

    // check validity
    if (p0_geometry.bottom() != p1_geometry.bottom()) {
        qCritical() << "bottom of p0, p1 should be equal";
    }
    if (p0_geometry.top() != p1_geometry.top()) {
        qCritical() << "top of p0, p1 should be equal";
    }
    if (p0_geometry.width() != p1_geometry.width()) {
        qCritical() << "width of p0, p1 should be equal";
    }

    quint16 mainwindow_width  = abs (p1_geometry.x() -
                                     p0_geometry.x() -
                                     p0_geometry.width());
    quint16 mainwindow_height = p0_geometry.height();

    if (mainwindow_height > mainwindow_width) {
        qDebug() << "vsize=" << mainwindow_height << ", hsize=" << mainwindow_width;
        return;
    }

    // create widgets for left/right/central boxes
    quint16 toolbar_height = ui->mainToolBar->rect().height();
    Rect.setTop(p0_geometry.top()+toolbar_height+5);
    Rect.setBottom(p0_geometry.bottom()+toolbar_height+5);
    Rect.setLeft(p0_geometry.right() + 2);
    Rect.setRight(p1_geometry.left() - 2);
}

// -------------------------------------------------
void MainWindow::Init_GUI_Menu (void)
{
    qDebug() << "Init_GUI_Menu";

    // enable/disable push buttons
    ui->pushButton_Start->setEnabled(true);
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Move_Now->setWhatsThis("This is MoveNow button");
    ui->pushButton_Move_Now->setToolTip  ("This is MoveNow tooltip");
    ui->pushButton_Move_Now->setEnabled(false);
    ui->pushButton_Takeback->setEnabled(false);

    // init menu
    QAction *action_save = new QAction ("&Save", this);
    connect (action_save, SIGNAL(triggered()), this, SLOT(onSave()));

    QAction *action_load = new QAction ("&Load", this);
    connect (action_load, SIGNAL(triggered()), this, SLOT(onLoad()));

    QAction *action_options = new QAction("&Options", this);
    connect(action_options, SIGNAL(triggered()), this,
            SLOT(on_pushButton_Options_clicked()));

    QAction *action_quit = new QAction("&Quit", this);
    action_quit->setShortcut(tr("CTRL+Q"));
    connect(action_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(action_save);
    file->addAction(action_load);
    file->addSeparator();
    file->addAction(action_options);
    file->addSeparator();
    file->addAction(action_quit);

    QMenu *play = menuBar()->addMenu("&Play");
    QAction *action_start = new QAction ("&Start", this);
    connect (action_start, SIGNAL(triggered()), this,
              SLOT(on_pushButton_Start_clicked()));

    QAction *action_stop = new QAction ("Sto&p", this);
    connect (action_stop, SIGNAL(triggered()), this,
             SLOT(on_pushButton_Stop_clicked()));

    QAction *action_takeback = new QAction ("&Takeback", this);
    connect (action_takeback, SIGNAL(triggered()), this,
             SLOT(on_pushButton_Takeback_clicked()));

    QAction *action_movenow = new QAction ("&Move now", this);
    connect (action_movenow, SIGNAL(triggered()), this,
             SLOT(on_pushButton_Move_Now_clicked()));

    play->addAction(action_start);
    play->addAction(action_stop);
    play->addAction(action_takeback);
    play->addAction(action_movenow);

    QMenu* help = menuBar()->addMenu("&Help");
    QAction *action_about = new QAction ("&About", this);
    connect (action_about, SIGNAL(triggered()), this, SLOT(onAbout()));
    QAction *action_author = new QAction ("&A&uthor", this);
    connect (action_author, SIGNAL(triggered()), this, SLOT(onAuthor()));

    help->addAction(action_about);
    help->addAction(action_author);
}

//------------------------------------------------------------
void MainWindow::Init_Chips (void)
{
    quint16 square_side = ui->label_chips_number_0->rect().width();

    if (Chip_0 != NULL) {
        delete Chip_0;
    }
    Chip_0 = new pushbutton_chip (
                Configuration_Data.Chip0_Shape,
                Configuration_Data.Chip0_Color,
                Cell::bg_color, Cell::grid_color,
                this);
    QPoint label_topleft_0 = ui->label_chips_number_0->mapToParent(QPoint(0, 0));
    Chip_0->setParent(ui->groupBox_player_0);
    Chip_0->setGeometry(
                label_topleft_0.x(), label_topleft_0.y()+20, square_side, square_side);


    if (Chip_1 != NULL) {
        delete Chip_1;
    }
    Chip_1 = new pushbutton_chip (
                Configuration_Data.Chip1_Shape,
                Configuration_Data.Chip1_Color,
                Cell::bg_color, Cell::grid_color,
                this);
    QPoint label_topleft_1 = ui->label_chips_number_1->mapToParent(QPoint(0, 0));
    Chip_1->setParent(ui->groupBox_player_1);
    Chip_1->setGeometry(
                label_topleft_1.x(), label_topleft_1.y()+20, square_side, square_side);

    QString strChipsNumber;
    strChipsNumber.sprintf("%u (%u)", 0, Configuration_Data.Chips_Number);

    ui->label_player_name_0->setText(Configuration_Data.Player_0_Name);
    ui->label_player_name_1->setText(Configuration_Data.Player_1_Name);

    ui->label_chips_number_0->setText(strChipsNumber);
    ui->label_chips_number_1->setText(strChipsNumber);
}


//------------------------------------------------------------
void MainWindow::Init_Status_Bar(void)
{
    qDebug() << "Create_Status_Bar";
    DateTimeLabel = new QLabel(this);
    DateTimeLabel->setContentsMargins(3, 3, 3, 3);
    MovesLabel = new QLabel(this);
    MovesLabel->setContentsMargins(3, 3, 3, 3);
    statusBar()->addWidget(MovesLabel);
    statusBar()->addWidget(DateTimeLabel);
    Timer_Status = new QTimer(this);
    onTimer_TimeSlot();
    connect(Timer_Status, SIGNAL(timeout()), this, SLOT(onTimer_TimeSlot()));
    Timer_Status->start(1000);
}

// -------------------------------------------------
// paint events
// -------------------------------------------------
void MainWindow::Draw_Text (QPainter& painter, QString& Text)
{
    //qDebug() << "Draw_Text";
    painter.setPen(Qt::blue);
    //painter.setFont(QFont("Arial", 30));
    //painter.drawText(rect(), Qt::AlignCenter, Text);

    //painter.translate(25,25);
    //painter.setRenderHint(QPainter::Antialiasing);
    //pen.setColor(Qt::magenta);
    //painter.setPen(pen);

    //QFont font;
    //font.setPixelSize(15);
    //painter.setFont(font);
    //int size=200;
    //painter.drawText(QPointF(0,size+size/15),Text);
    Update_Status(Text);
}

// -------------------------------------------------
void MainWindow::Draw_Move_Sign (QPainter& painter, bool side)
{
    if (! Draw_Move_Sign_Flag)
        return;
    qDebug () << "Draw_Move_Sign" << side;

    int x0, x1, y0, y1;
    quint16 xc;
    QWidget* pWidget = side ? ui->groupBox_player_0 : ui->groupBox_player_1;
    pWidget->rect().getCoords(&x0, &y0, &x1, &y1);
    QPoint BottomLeft = pWidget->mapTo(this, QPoint(x0,y1));
    xc = BottomLeft.x() + (x0+x1)/2;
    painter.setBrush(QBrush(Qt::green));
    quint16 yc = BottomLeft.y() + 15;
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::yellow, 2);
    painter.setPen(pen);
    QBrush brush(Qt::green);
    painter.setBrush(brush);
    qDebug() << "draw_ellipse" << xc << ":" << yc;
    painter.drawEllipse(xc, yc, 10, 10);
}

// -------------------------------------------------
QString MainWindow::Game_Result_To_Str (WINNER game_result) {
    QString result;

    switch (game_result) {
    case Winner_0:
        result.sprintf("Player %s won. %s, you are loser",
                       qPrintable(ui->label_player_name_0->text()),
                       qPrintable(ui->label_player_name_1->text()));
        break;
    case Winner_1:
        result.sprintf("Player %s won. %s, you are loser",
                       qPrintable(ui->label_player_name_1->text()),
                       qPrintable(ui->label_player_name_0->text()));
        break;
    case Winner_Draw:
        result.sprintf("%s vs. %s - Draw",
                       qPrintable(ui->label_player_name_0->text()),
                       qPrintable(ui->label_player_name_1->text()));
        break;
    case Winner_Undefined:
        result.sprintf("Game was not finished");
        break;
    default:
        result.sprintf("Game_Result_To_Str: unknown value %d of game_result",
                       game_result);
        break;
    }

    return result;
}

// -------------------------------------------------
void MainWindow::Draw_Winner_Side (QPainter& painter)
{
    WINNER winner = game->Winner_get();
    for (int side=0; side<=1; side++) {
        QWidget* pWidget = side ? ui->groupBox_player_1 : ui->groupBox_player_0;

        quint16 toolbar_height = ui->mainToolBar->rect().height();
        QRect widget_rect = pWidget->geometry();
        widget_rect.setTop   (widget_rect.top()+toolbar_height+30);
        widget_rect.setBottom(widget_rect.bottom()+toolbar_height+15);

        QColor color;
        if (Press_To_Reset) {
            switch (winner) {
            case Winner_0:
                color = side ? game->loser_color : game->winner_color;
                break;
            case Winner_1:
                color = side ? game->winner_color : game->loser_color;
                break;
            case Winner_Draw:
                color = game->draw_color;
                break;
            case Winner_Undefined:
                qCritical() << "Undefined color";
                color = game->default_bg_color;
                break;
            }
        } else {
            color = default_bg_color;
        }
        painter.fillRect(widget_rect, color);
    }
}

// -------------------------------------------------
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    Draw_Move_Sign (painter, Active_Side);

    if (game != NULL) {
        Draw_Winner_Side (painter);
    }

    if (Press_To_Reset) {
        QString str = Game_Result_To_Str (game->Winner_get());
        Draw_Text(painter, str);
    }

    QWidget::paintEvent(event);
}
