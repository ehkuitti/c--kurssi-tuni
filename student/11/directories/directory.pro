TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    directoryhierarchy.cpp \
    cli.cpp

HEADERS += \
    directoryhierarchy.hh \
    cli.hh

DISTFILES += \
    data
