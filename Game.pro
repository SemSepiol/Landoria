QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17

SOURCES += \
        Graphics/Cell.cpp \
        Graphics/GameWindow.cpp \
        Graphics/Map.cpp \
        main.cpp \
        Controller/Game.cpp

HEADERS += \
    Graphics/Cell.h \
    Graphics/GameWindow.h \
    Graphics/IDrawObject.h \
    Graphics/IMap.h \
    Graphics/Map.h \
    IObject.h \
    Controller/Game.h \
    Controller/IGame.h
