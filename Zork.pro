TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    attacklistener.cpp \
    character.cpp \
    characterdeathlistener.cpp \
    defeatlistener.cpp \
    demon.cpp \
    dragon.cpp \
    enemy.cpp \
    enterroomlistener.cpp \
    eventmanager.cpp \
    exitlistener.cpp \
    game.cpp \
    golistener.cpp \
    infolistener.cpp \
    inputlistener.cpp \
    item.cpp \
    main.cpp \
    maplistener.cpp \
    player.cpp \
    restartlistener.cpp \
    robot.cpp \
    room.cpp \
    takelistener.cpp \
    teleportlistener.cpp \
    uselistener.cpp \
    victorylistener.cpp

DISTFILES += \
    main.txt

HEADERS += \
    attacklistener.h \
    character.h \
    characterdeathlistener.h \
    defeatlistener.h \
    demon.h \
    dragon.h \
    enemy.h \
    enterroomlistener.h \
    eventlistener.h \
    eventmanager.h \
    exitlistener.h \
    game.h \
    golistener.h \
    infolistener.h \
    inputlistener.h \
    item.h \
    maplistener.h \
    player.h \
    restartlistener.h \
    robot.h \
    room.h \
    takelistener.h \
    teleportlistener.h \
    uselistener.h \
    victorylistener.h
