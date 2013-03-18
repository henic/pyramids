// --------------------------------------------------------------------
// main.cpp
// --------------------------------------------------------------------

#include <QSharedMemory>
#include <QApplication>

#include <QDir>
#include <QtDebug>
#include <QFile>
#include <QTextStream>

#include "const_int.h"
#include "mainwindow.h"

#if HTTPGET_MODULE==1
#include "httpget.h"
#endif

// --------------------------------------------------------------------
static bool Use_Debug_File = false;
static QString Debug_File_Name = Debug_File_Name_Default;
QString& Get_Debug_File_Name (void) {return Debug_File_Name;}

static QString Execution_Directory = Execution_Directory_Default;

// --------------------------------------------------------------------
void customMessageHandler (
                QtMsgType type,
                const QMessageLogContext &context,
                const QString &msg)
{
    QString txt;
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        /*
        txt.sprintf("Debug: %s (%s:%u, %s)\n",
                    localMsg.constData(), context.file,
                    context.line, context.function);
        */
        txt.sprintf("%s", localMsg.constData());
        break;
    case QtWarningMsg:
        txt.sprintf("Warning: %s (%s:%u, %s)\n",
                    localMsg.constData(), context.file,
                    context.line, context.function);
        break;
    case QtCriticalMsg:
        txt.sprintf("Critical: %s (%s:%u, %s)\n",
                    localMsg.constData(), context.file,
                    context.line, context.function);
        break;
    case QtFatalMsg:
        txt.sprintf("Fatal: %s (%s:%u, %s)\n",
                    localMsg.constData(), context.file,
                    context.line, context.function);
        break;
    }

    QFile outFile (Debug_File_Name);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;

    if (type==QtFatalMsg)
        abort();
}

// --------------------------------------------------------------------
static void Usage (void) {
    qDebug() << "Usage:" << Application_Name <<
                "[-log <filename>] [-dir <execution_dir>]";
}

// --------------------------------------------------------------------
static bool First_Argument_Is_Help (const char* Arg) {
    return (Arg[0]=='?' ||
            !strnicmp(Arg, "help",  4)  ||
            !strnicmp(Arg, "-help", 5) ||
            !strnicmp(Arg, "-?", 2) ||
            !strnicmp(Arg, "/?", 2));
}

// --------------------------------------------------------------------
static int Proceed_Arguments (int argc, char *argv[])
{
    if (argc==1)
        return 0;


    qDebug() << "===== " << argc << "args =====";
    for (int i=0; i<argc; i++) {
      qDebug() << "argv#" << i << "=" << argv[i];
    }


    // help pattern search: some patterns
    if (First_Argument_Is_Help(argv[1]))
    {
        Usage ();
        return 1;
    }

    int i=1;
    while (i<argc) {
        if (!strnicmp (argv[1], "-log", 4)) {
            if (++i == argc) {
                qDebug () << "logfile name expected after -log ";
                return 2;
            }
            else {
                Use_Debug_File  = true;
                Debug_File_Name = argv[i];
            }
        }
        else
        if (!strnicmp (argv[1], "-dir", 4)) {
            if (++i == argc) {
                qDebug () << "directory name expected after -dir ";
                return 3;
            }
            else {
                Execution_Directory = argv[i];
            }
        }
        else {
            qDebug () << "Unknown option" << argv[1] << "not supported yet";
            return 4;
        }
        i++;
    }

    return 0;
}

// --------------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc > 1) {
        int rc = Proceed_Arguments (argc, argv);
        if (rc) {
            qCritical() << "Proceed_Arguments returned" << rc;
            return 1;
        }
    }

    if (Execution_Directory[0]!='\0' &&
        Execution_Directory != Execution_Directory_Default) {
        //QString CurrentDir = QApplication::applicationDirPath();
        //qDebug() << "CurrentDir " << CurrentDir;
        QDir::setCurrent(Execution_Directory);

    }

    QFile::remove (Debug_File_Name);

    if (Use_Debug_File)
        qInstallMessageHandler(customMessageHandler);

    // check that no another copy of the application is running
    QSharedMemory shared(Shared_Memory_Unique_Label);
    if( !shared.create( 512, QSharedMemory::ReadWrite) )
        return 0;

#if HTTPGET_MODULE==1
    HttpGet http_request (Quotes_Http_Server); //test, TBD
#endif

    QApplication app(argc, argv);
    app.setApplicationVersion(Version_String);
    app.setApplicationName   (Application_Name);
    app.setOrganizationDomain("henic.livejournal.com");
    app.setOrganizationName  ("Tigers Ltd");

    MainWindow w;
    w.show();
    return app.exec();
}

// --------------------------------------------------------------------
