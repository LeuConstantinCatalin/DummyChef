QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    bucatar.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    meniu.cpp \
    retete.cpp \
    signup.cpp \
    user.cpp \
    utilizator.cpp

HEADERS += \
    admin.h \
    bucatar.h \
    login.h \
    mainwindow.h \
    meniu.h \
    retete.h \
    signup.h \
    user.h \
    utilizator.h

FORMS += \
    admin.ui \
    bucatar.ui \
    login.ui \
    mainwindow.ui \
    retete.ui \
    signup.ui \
    utilizator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target