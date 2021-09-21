QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17

SOURCES += \
        Controller/Calculations.cpp \
        Graphics/Buildings/Town.cpp \
        Graphics/Cell.cpp \
        Graphics/Fubrics/FactoryBuild.cpp \
        Graphics/Fubrics/FactoryPixmap.cpp \
        Graphics/Fubrics/FactoryRes.cpp \
        Graphics/Fubrics/FactoryUnits.cpp \
        Graphics/GameWindow.cpp \
        Graphics/Map.cpp \
        Graphics/Resources/Res.cpp \
        Graphics/Units/Unit.cpp \
        main.cpp \
        Controller/Game.cpp

HEADERS += \
    Controller/Calculations.h \
    Controller/Enums.h \
    Graphics/Buildings/IBuilding.h \
    Graphics/Buildings/Town.h \
    Graphics/Cell.h \
    Graphics/Fubrics/FactoryBuild.h \
    Graphics/Fubrics/FactoryPixmap.h \
    Graphics/Fubrics/FactoryRes.h \
    Graphics/Fubrics/FactoryUnits.h \
    Graphics/GameWindow.h \
    Graphics/IBuild.h \
    Graphics/ICell.h \
    Graphics/IContent.h \
    Graphics/IDrawObject.h \
    Graphics/IMap.h \
    Graphics/IRes.h \
    Graphics/IUnit.h \
    Graphics/Map.h \
    Graphics/Resources/Aluminum.h \
    Graphics/Resources/Coal.h \
    Graphics/Resources/Fish.h \
    Graphics/Resources/Gold.h \
    Graphics/Resources/Horses.h \
    Graphics/Resources/IRes.h \
    Graphics/Resources/Iron.h \
    Graphics/Resources/Oil.h \
    Graphics/Resources/Res.h \
    Graphics/Resources/Silver.h \
    Graphics/Resources/Stone.h \
    Graphics/Resources/Uranium.h \
    Graphics/Units/Bowman.h \
    Graphics/Units/Citizen.h \
    Graphics/Units/IUnit.h \
    Graphics/Units/Swordsman.h \
    Graphics/Units/Unit.h \
    Graphics/Units/Worker.h \
    IObject.h \
    Controller/Game.h \
    Controller/IGame.h

RESOURCES += \
    Images.qrc
