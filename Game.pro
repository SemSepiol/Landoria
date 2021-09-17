QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17

SOURCES += \
        Controller/Calculations.cpp \
        Graphics/Buildings/Town.cpp \
        Graphics/Cell.cpp \
        Graphics/GameWindow.cpp \
        Graphics/Map.cpp \
        Graphics/Resources/Iron.cpp \
        Graphics/Units/Worker.cpp \
        main.cpp \
        Controller/Game.cpp

HEADERS += \
    Controller/Calculations.h \
    Controller/Enums.h \
    Graphics/Buildings/IBuilding.h \
    Graphics/Buildings/Town.h \
    Graphics/Cell.h \
    Graphics/GameWindow.h \
    Graphics/IBuild.h \
    Graphics/ICell.h \
    Graphics/IContent.h \
    Graphics/IDrawObject.h \
    Graphics/IMap.h \
    Graphics/IRes.h \
    Graphics/IUnit.h \
    Graphics/Map.h \
    Graphics/Resources/IRes.h \
    Graphics/Resources/Iron.h \
    Graphics/Units/IUnit.h \
    Graphics/Units/Worker.h \
    IObject.h \
    Controller/Game.h \
    Controller/IGame.h
