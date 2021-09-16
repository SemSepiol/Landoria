QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17

SOURCES += \
        Controller/Calculations.cpp \
        Graphics/Cell.cpp \
        Graphics/GameWindow.cpp \
        Graphics/Map.cpp \
        Graphics/Units/Worker.cpp \
        main.cpp \
        Controller/Game.cpp

HEADERS += \
    Controller/Calculations.h \
    Controller/Enums.h \
    Graphics/Cell.h \
    Graphics/GameWindow.h \
    Graphics/ICell.h \
    Graphics/IContent.h \
    Graphics/IDrawObject.h \
    Graphics/IMap.h \
    Graphics/IUnit.h \
    Graphics/Map.h \
    Graphics/Units/IUnit.h \
    Graphics/Units/Worker.h \
    IObject.h \
    Controller/Game.h \
    Controller/IGame.h
