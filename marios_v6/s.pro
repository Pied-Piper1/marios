QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    block.cpp \
    box.cpp \
    brick.cpp \
    debris.cpp \
    fireball.cpp \
    flower.cpp \
    goomba.cpp \
    lift.cpp \
    main.cpp \
    mario.cpp \
    money.cpp \
    mushroom.cpp \
    object.cpp \
    pipe.cpp \
    turtle.cpp \
    view.cpp \
    wall.cpp

HEADERS += \
    background.h \
    block.h \
    box.h \
    brick.h \
    debris.h \
    fireball.h \
    flower.h \
    goomba.h \
    lift.h \
    mario.h \
    money.h \
    mushroom.h \
    object.h \
    pipe.h \
    turtle.h \
    util.h \
    view.h \
    wall.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
