QT       += core gui network
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    bucatar.cpp \
    cuser.cpp \
    isign.cpp \
    iuser.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    serverconector.cpp \
    sig.cpp \
    signfactory.cpp \
    signup.cpp \
    userfactory.cpp \
    utilizator.cpp

HEADERS += \
    admin.h \
    bucatar.h \
    cuser.h \
    isign.h \
    iuser.h \
    login.h \
    mainwindow.h \
    serverconector.h \
    sig.h \
    signfactory.h \
    signup.h \
    userfactory.h \
    utilizator.h

FORMS += \
    bucatar.ui \
    cuser.ui \
    mainwindow.ui \
    sig.ui \
    signup.ui \
    utilizator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
