QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17


RESOURCES += \
    Images.qrc

HEADERS += \
    Controllers/Enums.h \
    Controllers/Game.h \
    Controllers/IGame.h \
    Controllers/IPlayer.h \
    Controllers/Player.h \
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
    Graphics/FubricUnits.h \
    Graphics/GameWindow.h \
    Graphics/GraphicsController/AGraphicsController.h \
    Graphics/GraphicsController/Calculations.h \
    Graphics/GraphicsController/CreateMap.h \
    Graphics/GraphicsController/EventsStructures.h \
    Graphics/GraphicsController/GraphicsController.h \
    Graphics/GraphicsController/IGraphicsController.h \
    Graphics/ICell.h \
    Graphics/IContent.h \
    Graphics/IDrawObject.h \
    Graphics/IMap.h \
    Graphics/Map.h \
    Graphics/Menus/IMenu.h \
    Graphics/Menus/UpperMenu.h \
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
    IObject.h

SOURCES += \
    Controllers/Game.cpp \
    Controllers/Player.cpp \
    Graphics/Buildings/Building.cpp \
    Graphics/Cell.cpp \
    Graphics/Factories/FactoryBuild.cpp \
    Graphics/Factories/FactoryPixmap.cpp \
    Graphics/Factories/FactoryRes.cpp \
    Graphics/Factories/FactoryUnits.cpp \
    Graphics/GameWindow.cpp \
    Graphics/GraphicsController/AGraphicsController.cpp \
    Graphics/GraphicsController/Calculations.cpp \
    Graphics/GraphicsController/CreateMap.cpp \
    Graphics/GraphicsController/GraphicsController.cpp \
    Graphics/Map.cpp \
    Graphics/Menus/UpperMenu.cpp \
    Graphics/Resources/Res.cpp \
    Graphics/Units/Unit.cpp \
    main.cpp

