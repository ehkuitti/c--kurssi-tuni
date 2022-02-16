QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    gameboard.cpp \
    square.cpp

HEADERS += \
    gameboard.hh \
    square.hh \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icons/0.png \
    icons/1.png \
    icons/2.png \
    icons/3.png \
    icons/4.png \
    icons/5.png \
    icons/6.png \
    icons/7.png \
    icons/8.png \
    icons/bomb.png \
    icons/closedSquare.png \
    icons/flagged.png
