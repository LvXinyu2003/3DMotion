QT       += core gui opengl
QT       += core gui multimedia
QT       += network
QT       += core gui sql
QT       +=testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += -L$$PWD/OpenSSL-Win32/lib/ -llibssl
LIBS += -L$$PWD/OpenSSL-Win32/lib/ -llibcrypto

INCLUDEPATH += $$PWD/OpenSSL-Win32/include
DEPENDPATH += $$PWD/OpenSSL-Win32/include

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LogHandler.cpp \
    chatclient.cpp \
    glwidget.cpp \
    joy_thread.cpp \
    joystick.cpp \
    main.cpp \
    dialog.cpp \
    mainwindow.cpp \
    zaux.cpp \
    audio.cpp \
    http.cpp \
    speech.cpp

HEADERS += \
    LogHandler.h \
    chatclient.h \
    dialog.h \
    glwidget.h \
    joy_thread.h \
    joystick.h \
    mainwindow.h \
    zaux.h \
    audio.h \
    http.h \
    speech.h

FORMS += \
    dialog.ui \
    mainwindow.ui

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/libs/ -lzmotion
unix|win32: LIBS += -L$$PWD/libs/ -lglu32 -lopengl32

INCLUDEPATH += $$PWD/includes
DEPENDPATH += $$PWD/includes
