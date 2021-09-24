QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17

SOURCES += \
        Controller/Calculations.cpp \
        Controller/CreateMap.cpp \
        Graphics/Buildings/Building.cpp \
        Graphics/Cell.cpp \
        Graphics/Factories/FactoryBuild.cpp \
        Graphics/Factories/FactoryPixmap.cpp \
        Graphics/Factories/FactoryRes.cpp \
        Graphics/Factories/FactoryUnits.cpp \
        Graphics/GameWindow.cpp \
        Graphics/Map.cpp \
        Graphics/Resources/Res.cpp \
        Graphics/Units/Unit.cpp \
        main.cpp \
        Controller/Game.cpp

HEADERS += \
    Controller/Calculations.h \
    Controller/CreateMap.h \
    Controller/Enums.h \
    Graphics/Buildings/Building.h \
    Graphics/Buildings/Farm.h \
    Graphics/Buildings/FishingBoats.h \
    Graphics/Buildings/Fort.h \
    Graphics/Buildings/LumberMill.h \
    Graphics/Buildings/Mine.h \
    Graphics/Buildings/OilWell.h \
    Graphics/Buildings/Pasture.h \
    Graphics/Buildings/Quarry.h \
    Graphics/Buildings/Town.h \
    Graphics/Buildings/TradingPost.h \
    Graphics/Cell.h \
    Graphics/Factories/FactoryBuild.h \
    Graphics/Factories/FactoryPixmap.h \
    Graphics/Factories/FactoryRes.h \
    Graphics/Factories/FactoryUnits.h \
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
    Graphics/Resources/Iron.h \
    Graphics/Resources/Oil.h \
    Graphics/Resources/Res.h \
    Graphics/Resources/Silver.h \
    Graphics/Resources/Stone.h \
    Graphics/Resources/Uranium.h \
    Graphics/Units/Bowman.h \
    Graphics/Units/Citizen.h \
    Graphics/Units/Swordsman.h \
    Graphics/Units/Unit.h \
    Graphics/Units/Worker.h \
    IObject.h \
    Controller/Game.h \
    Controller/IGame.h

RESOURCES += \
    Images.qrc
