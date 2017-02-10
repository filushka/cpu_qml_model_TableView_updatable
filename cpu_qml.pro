TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    fileio.cpp \
    tableviewmodel.cpp

#RESOURCES = qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


HEADERS += \
    fileio.h \
    tableviewmodel.h

#include("rcc.pri")

RESOURCES += \
    qml.qrc
