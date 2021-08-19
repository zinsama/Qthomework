QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chessboard.cpp \
    dialog_connect_to_server.cpp \
    dialog_create_the_connection.cpp \
    main.cpp \
    mainwindow.cpp \
    pieces.cpp

HEADERS += \
    chessboard.h \
    dialog_connect_to_server.h \
    dialog_create_the_connection.h \
    mainwindow.h \
    pieces.h

FORMS += \
    dialog_connect_to_server.ui \
    dialog_create_the_connection.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
