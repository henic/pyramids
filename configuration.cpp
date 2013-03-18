// -------------------------------------------------
// configuration.cpp
// -------------------------------------------------

#include <QDebug>
#include "QFile"
#include "QString"
#include "QColor"
#include "QSettings"

#include "cell.h"
#include "configuration.h"

static const char crlf[] = "\r\n";

// -------------------------------------------------

// -------------------------------------------------
static const    quint16 Board_Size_Default               = 8;
static const    quint16 Chips_Number_Default            = 12;
static const    quint16 Chain_Length_Default            = 4;

static const    bool    First_Is_Computer_Default       = true;
static const    quint16 First_Computer_Level_Default    = 1;
static const    bool    Second_Is_Computer_Default      = true;
static const    quint16 Second_Computer_Level_Default   = 1;
static const    bool    Show_Tip_Default                = false;
static const    quint16 Delay_Show_Tip_Default          = 3; // sec
static const    bool    Show_Threat_Default             = false;
static const    quint16 Delay_Show_Threat_Default       = 3; // sec
static const    bool    Limit_Move_Time_Default         = false;
static const    quint16 Limit_Move_Time_Sec_Default     = 10; // sec
static const    quint16 Delay_Betweeen_Computer_Moves_Default = 1; // sec
static const    quint16 Comp_Search_Depth_Default       = 1;
static const    quint16 Moves_Search_Range_Default      = 1;
static const    bool    Skip_Confirmation_Default       = true;

static const    SHAPE_KIND  Chip0_Shape_Default         = SHAPE_ROUND;
static const    int         Chip0_Color_r_Default       = 0xFF;
static const    int         Chip0_Color_g_Default       = 0xFF;
static const    int         Chip0_Color_b_Default       = 0x0;
static const    QColor      Chip0_Color_Default         = Qt::yellow; // not in use
static const    SHAPE_KIND  Chip1_Shape_Default         = SHAPE_ROUND;
static const    int         Chip1_Color_r_Default       = 0x0;
static const    int         Chip1_Color_g_Default       = 0x0;
static const    int         Chip1_Color_b_Default       = 0xFF;
static const    QColor      Chip1_Color_Default         = Qt::blue;

static const    QString     Player_0_Name_Default       ("Vasya");
static const    QString     Player_1_Name_Default       ("Petya");

// -------------------------------------------------
static const CONFIGURATION_USERDEF Configuration_Default =
{
    Board_Size_Default,
    Chips_Number_Default,
    Chain_Length_Default,

    First_Is_Computer_Default,
    First_Computer_Level_Default,
    Second_Is_Computer_Default,
    Second_Computer_Level_Default,
    Show_Tip_Default,
    Delay_Show_Tip_Default,
    Show_Threat_Default,
    Delay_Show_Threat_Default,
    Limit_Move_Time_Default,
    Limit_Move_Time_Sec_Default,
    Delay_Betweeen_Computer_Moves_Default,
    Comp_Search_Depth_Default,
    Moves_Search_Range_Default,
    Skip_Confirmation_Default,
    Chip0_Shape_Default,
    Chip0_Color_Default,
    Chip0_Color_r_Default, Chip0_Color_g_Default, Chip0_Color_b_Default,
    Chip1_Shape_Default,
    Chip1_Color_Default,
    Chip1_Color_r_Default, Chip1_Color_g_Default, Chip1_Color_b_Default,
    Player_0_Name_Default,
    Player_1_Name_Default
};

// -------------------------------------------------
/*
static quint16 GetUInt16 (QString s)
{
    int IndexOfEqual = s.lastIndexOf("=");
    if (IndexOfEqual<0)
        return 0;
    return s.mid(IndexOfEqual+1).toUShort();
}

// -------------------------------------------------
static
char* Get_Qstring (QString s)
{
    int IndexOfEqual = s.lastIndexOf("=");
    if (IndexOfEqual<0)
        return (char*) "";
    static char sResult[128];
    QString temp_result = s.mid(IndexOfEqual+1);
    strcpy (sResult, qPrintable (temp_result));
    return sResult;
}
*/

// -------------------------------------------------
static
void Configuration_To_QString (const CONFIGURATION_USERDEF& Configuration,
                               QString& s) // result
{
    s.clear();

    s += "Board_Size = " +
            QString::number(Configuration.Board_Size)+ crlf;

    s += "Chips_Number = " +
            QString::number(Configuration.Chips_Number)+ crlf;

    s += "Chain_Length = " +
            QString::number(Configuration.Chain_Length)+ crlf;

    s += "First_Is_Computer = " +
            QString::number(Configuration.First_Is_Computer)+ crlf;

    s += "First_Computer_Level = " +
            QString::number(Configuration.First_Computer_Level)+ crlf;

    s += "Second_Is_Computer = " +
            QString::number(Configuration.Second_Is_Computer)+ crlf;

    s += "Second_Computer_Level = " +
            QString::number(Configuration.Second_Computer_Level)+ crlf;

    s += "Show_Tip = " +
            QString::number(Configuration.Show_Tip)+ crlf;

    s += "Delay_Show_Tip = " +
            QString::number(Configuration.Delay_Show_Tip)+ crlf;

    s += "Show_Threat = " +
            QString::number(Configuration.Show_Threat)+ crlf;

    s += "Delay_Show_Threat = " +
            QString::number(Configuration.Delay_Show_Threat)+ crlf;

    s += "Limit_Move_Time = " +
            QString::number(Configuration.Limit_Move_Time)+ crlf;

    s += "Limit_Move_Time_Sec = " +
            QString::number(Configuration.Limit_Move_Time_Sec)+ crlf;

    s += "Delay_Betweeen_Computer_Moves = " +
            QString::number(Configuration.Delay_Betweeen_Computer_Moves)+ crlf;

    s += "Comp_Search_Depth = " +
            QString::number(Configuration.Comp_Search_Depth)+ crlf;

    s += "Moves_Search_Range = " +
            QString::number(Configuration.Moves_Search_Range)+ crlf;

    s += "Skip_Confirmation = " +
            QString::number(Configuration.Skip_Confirmation)+ crlf;

    s += "Chip0_Shape = " +
            QString::number(Configuration.Chip0_Shape)+ crlf;

    int r,g,b;
    Configuration.Chip0_Color.getRgb(&r,&g,&b);
    s += "Chip0_r = " + QString::number(r)+ crlf;
    s += "Chip0_g = " + QString::number(g)+ crlf;
    s += "Chip0_b = " + QString::number(b)+ crlf;

    s += "Chip1_Shape = " +
            QString::number(Configuration.Chip1_Shape)+ crlf;
    Configuration.Chip1_Color.getRgb(&r,&g,&b);
    s += "Chip1_r = " + QString::number(r)+ crlf;
    s += "Chip1_g = " + QString::number(g)+ crlf;
    s += "Chip1_b = " + QString::number(b)+ crlf;

    s += "Player_0_Name = " + (QString)Configuration.Player_0_Name + crlf;
    s += "Player_1_Name = " + (QString)Configuration.Player_1_Name + crlf;

}

// -------------------------------------------------
static
void Configuration_Print (const CONFIGURATION_USERDEF& Configuration)
{
    QString s;
    Configuration_To_QString (Configuration, s);
    qDebug() << s;
}

// -------------------------------------------------
void Configuration_Load (
                    CONFIGURATION_USERDEF& Configuration,
                    const QString& filename,
                    const bool Print)
{
    qDebug() << "Configuration_Load" << filename << "Print=" << Print;

    QSettings* settings = new QSettings (filename, QSettings::IniFormat);
    Configuration = Configuration_Default; // use default values if no file

    if(filename.isEmpty()) // use default if no filename passed
        return;            // well it's unnecessary: next check contains it
    if (! QFile::exists(filename))
        return;

    Configuration.Board_Size            = settings->value("Desk/Board_size",    Board_Size_Default).toInt();
    Configuration.Chips_Number          = settings->value("Desk/Chips_Number",  Chips_Number_Default).toInt();
    Configuration.Chain_Length          = settings->value("Desk/Chain_Length",  Chain_Length_Default).toInt();

    Configuration.Show_Tip              = settings->value("Game/Show_Tip",      Show_Tip_Default).toInt();
    Configuration.Delay_Show_Tip        = settings->value("Game/Delay_Show_Tip",Delay_Show_Tip_Default).toInt();
    Configuration.Show_Threat           = settings->value("Game/Show_Threat",   Show_Threat_Default).toInt();
    Configuration.Delay_Show_Threat     = settings->value("Game/Delay_Show_Threat", Delay_Show_Threat_Default).toInt();
    Configuration.Limit_Move_Time       = settings->value("Game/Limit_Move_Time",   Limit_Move_Time_Default).toInt();
    Configuration.Limit_Move_Time_Sec   = settings->value("Game/Limit_Move_Time_Sec", Limit_Move_Time_Sec_Default).toInt();
    Configuration.Delay_Betweeen_Computer_Moves = settings->value("Game/Delay_Betweeen_Computer_Moves", Delay_Betweeen_Computer_Moves_Default).toInt();
    Configuration.Comp_Search_Depth     = settings->value("Game/Comp_Search_Depth",  Comp_Search_Depth_Default).toInt();
    Configuration.Moves_Search_Range    = settings->value("Game/Moves_Search_Range", Moves_Search_Range_Default).toInt();
    Configuration.Skip_Confirmation     = settings->value("Game/Skip_Confirmation",  Skip_Confirmation_Default).toInt();



    Configuration.Chip0_Shape           = (SHAPE_KIND) settings->value("Chip_Config/Chip0_Shape",  Chip0_Shape_Default).toInt();
    Configuration.Chip0_Color_r         = settings->value("Chip_Config/Chip0_Color_r", Chip0_Color_r_Default).toInt();
    Configuration.Chip0_Color_g         = settings->value("Chip_Config/Chip0_Color_g", Chip0_Color_g_Default).toInt();
    Configuration.Chip0_Color_b         = settings->value("Chip_Config/Chip0_Color_b", Chip0_Color_b_Default).toInt();
    Configuration.Chip0_Color           = QColor (Configuration.Chip0_Color_r, Configuration.Chip0_Color_g, Configuration.Chip0_Color_b);

    Configuration.Chip1_Shape           = (SHAPE_KIND) settings->value("Chip_Config/Chip1_Shape",  Chip1_Shape_Default).toInt();
    Configuration.Chip1_Color_r         = settings->value("Chip_Config/Chip1_Color_r", Chip1_Color_r_Default).toInt();
    Configuration.Chip1_Color_g         = settings->value("Chip_Config/Chip1_Color_g", Chip1_Color_g_Default).toInt();
    Configuration.Chip1_Color_b         = settings->value("Chip_Config/Chip1_Color_b", Chip1_Color_b_Default).toInt();
    Configuration.Chip1_Color           = QColor (Configuration.Chip1_Color_r, Configuration.Chip1_Color_g, Configuration.Chip1_Color_b);

    Configuration.Player_0_Name         = settings->value("Players/Player_0_Name",  Player_0_Name_Default).toString();
    Configuration.Player_1_Name         = settings->value("Players/Player_1_Name",  Player_1_Name_Default).toString();

    Configuration.First_Is_Computer     = settings->value("Players/First_Is_Computer",      First_Is_Computer_Default).toInt();
    Configuration.First_Computer_Level  = settings->value("Players/First_Computer_Level",   First_Computer_Level_Default).toInt();
    Configuration.Second_Is_Computer    = settings->value("Players/Second_Is_Computer",     Second_Is_Computer_Default).toInt();
    Configuration.Second_Computer_Level = settings->value("Players/Second_Computer_Level",  Second_Computer_Level_Default).toInt();


    //!!! move out
    // chips number no more of total cells number
    if (Configuration.Chips_Number > Configuration.Board_Size*Configuration.Board_Size/2)
        Configuration.Chips_Number = Configuration.Board_Size*Configuration.Board_Size/2;

    if (Print)
        Configuration_Print(Configuration);
}

// -------------------------------------------------
void Configuration_Save (
                    const CONFIGURATION_USERDEF& Configuration,
                    const QString& filename)
{
    qDebug() << "Configuration_Save" << filename;

    if(filename.isEmpty()) // use default if no filename passed
        return;            // well it's unnecessary: next check contains it

    QSettings* settings = new QSettings (filename, QSettings::IniFormat);

    settings->setValue("Desk/Board_size",    Configuration.Board_Size);
    settings->setValue("Desk/Chips_Number", Configuration.Chips_Number);
    settings->setValue("Desk/Chain_Length", Configuration.Chain_Length);

    settings->setValue("Game/Show_Tip",             (int)Configuration.Show_Tip);
    settings->setValue("Game/Delay_Show_Tip",       Configuration.Delay_Show_Tip);
    settings->setValue("Game/Show_Threat",          (int)Configuration.Show_Threat);
    settings->setValue("Game/Delay_Show_Threat",    Configuration.Delay_Show_Threat);
    settings->setValue("Game/Limit_Move_Time",      (int)Configuration.Limit_Move_Time);
    settings->setValue("Game/Limit_Move_Time_Sec",  Configuration.Limit_Move_Time_Sec);
    settings->setValue("Game/Delay_Betweeen_Computer_Moves", Configuration.Delay_Betweeen_Computer_Moves);
    settings->setValue("Game/Comp_Search_Depth",    Configuration.Comp_Search_Depth);
    settings->setValue("Game/Moves_Search_Range",   Configuration.Moves_Search_Range);
    settings->setValue("Game/Skip_Confirmation",    (int)Configuration.Skip_Confirmation);

    settings->setValue("Chip_Config/Chip0_Shape",   Configuration.Chip0_Shape);
    settings->setValue("Chip_Config/Chip0_Color_r", Configuration.Chip0_Color_r);
    settings->setValue("Chip_Config/Chip0_Color_g", Configuration.Chip0_Color_g);
    settings->setValue("Chip_Config/Chip0_Color_b", Configuration.Chip0_Color_b);
    settings->setValue("Chip_Config/Chip1_Shape",   Configuration.Chip1_Shape);
    settings->setValue("Chip_Config/Chip1_Color_r", Configuration.Chip1_Color_r);
    settings->setValue("Chip_Config/Chip1_Color_g", Configuration.Chip1_Color_g);
    settings->setValue("Chip_Config/Chip1_Color_b", Configuration.Chip1_Color_b);


    settings->setValue("Players/Player_0_Name",         Configuration.Player_0_Name);
    settings->setValue("Players/Player_1_Name",         Configuration.Player_1_Name);
    settings->setValue("Players/First_Is_Computer",     (int)Configuration.First_Is_Computer);
    settings->setValue("Players/First_Computer_Level",  Configuration.First_Computer_Level);
    settings->setValue("Players/Second_Is_Computer",    (int)Configuration.Second_Is_Computer);
    settings->setValue("Players/Second_Computer_Level", Configuration.Second_Computer_Level);
}

