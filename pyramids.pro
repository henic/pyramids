#-------------------------------------------------
#
# Project created by QtCreator 2012-09-26T07:22:33
#
#-------------------------------------------------

QT += core gui network declarative widgets

CONFIG  += qt thread warn_on

TARGET   = pyramids
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp \
    mainwindow_draw.cpp \
    options.cpp \
    game.cpp \
    board.cpp \
    configuration.cpp \
    cell.cpp \
    chip_options.cpp \
    pushbutton_chip.cpp \
    estimation.cpp \
    httpget.cpp \
    chkheap.cpp \
    serv.cpp

HEADERS  += \
    mainwindow.h \
    options.h \
    game.h \
    types_int.h \
    board.h \
    configuration.h \
    configuration_typedef.h \
    cell.h \
    chip_options.h \
    pushbutton_chip.h \
    estimation.h \
    httpget.h \
    const_int.h \
    chkheap.h \
    serv.h

FORMS    += mainwindow.ui \
    options.ui \
    confirmation.ui \
    chip_options.ui

RESOURCES += \
    pyramids.qrc

OTHER_FILES +=
