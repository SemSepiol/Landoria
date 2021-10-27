QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17


RESOURCES += \
    Images.qrc

HEADERS += \
    Controllers/BuildingCharaterichtics.h \
    Controllers/Enums.h \
    Controllers/FindUnitVision.h \
    Controllers/FindUnitWay.h \
    Controllers/Game.h \
    Controllers/IGame.h \
    Controllers/Player/IMenuTownPlayer.h \
    Controllers/Player/IPlayer.h \
    Controllers/Player/Player.h \
    Controllers/Player/PlayerBuild.h \
    Controllers/Player/PlayerMap.h \
    Controllers/Player/PlayerRes.h \
    Controllers/Player/PlayerScience.h \
    Controllers/Player/PlayerTown.h \
    Controllers/Player/PlayerUnit.h \
    Controllers/TownBuildNeeds.h \
    Controllers/TownBuildings.h \
    Controllers/UnitsCharaterichtics.h \
    Graphics/Buildings/Building.h \
    Graphics/Buildings/Farm.h \
    Graphics/Buildings/FishingBoat.h \
    Graphics/Buildings/Fort.h \
    Graphics/Buildings/LumberMill.h \
    Graphics/Buildings/Mine.h \
    Graphics/Buildings/OilWell.h \
    Graphics/Buildings/Pasture.h \
    Graphics/Buildings/Quarry.h \
    Graphics/Buildings/Town.h \
    Graphics/Buildings/TradingPost.h \
    Graphics/Cell.h \
    Graphics/DrawWay.h \
    Graphics/Factories/FactoryBuild.h \
    Graphics/Factories/FactoryColor.h \
    Graphics/Factories/FactoryMenusUnit.h \
    Graphics/Factories/FactoryPixmap.h \
    Graphics/Factories/FactoryRes.h \
    Graphics/Factories/FactoryString.h \
    Graphics/Factories/FactoryUnits.h \
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
    Graphics/MenuTown.h \
    Graphics/MenuTown/AWidgetTown.h \
    Graphics/MenuTown/IMenuTown.h \
    Graphics/MenuTown/InformWidget.h \
    Graphics/MenuTown/MenuAlreadyBuildTown.h \
    Graphics/MenuTown/MenuBuildTown.h \
    Graphics/MenuTown/MenuQueueTown.h \
    Graphics/MenuTown/MenuTown.h \
    Graphics/MenuTown/MenuTypeWorkTown.h \
    Graphics/MenuTown/WidgetTownBuilding.h \
    Graphics/MenuTown/WidgetTownUnit.h \
    Graphics/Menus/AMenuForUnit.h \
    Graphics/Menus/AMenuInWindow.h \
    Graphics/Menus/BottomMenu.h \
    Graphics/Menus/CitizenMenu.h \
    Graphics/Menus/UpperMenu.h \
    Graphics/Menus/WarriorMenu.h \
    Graphics/Menus/WorkerMenu.h \
    Graphics/Minimap.h \
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
    Graphics/InformationWidgets/UnitInformation.h \
    Graphics/Units/Bowman.h \
    Graphics/Units/Citizen.h \
    Graphics/Units/Swordsman.h \
    Graphics/Units/Unit.h \
    Graphics/Units/Worker.h \
    IObject.h

SOURCES += \
    Controllers/FindUnitWay.cpp \
    Controllers/Game.cpp \
    Controllers/FindUnitVision.cpp \
    Controllers/Player/Player.cpp \
    Controllers/Player/PlayerMap.cpp \
    Controllers/Player/PlayerRes.cpp \
    Controllers/Player/PlayerScience.cpp \
    Controllers/Player/PlayerTown.cpp \
    Controllers/TownBuildNeeds.cpp \
    Graphics/Buildings/Building.cpp \
    Graphics/Buildings/Town.cpp \
    Graphics/Cell.cpp \
    Graphics/ControlContents.cpp \
    Graphics/DrawWay.cpp \
    Graphics/Factories/FactoryBuild.cpp \
    Graphics/Factories/FactoryColor.cpp \
    Graphics/Factories/FactoryMenusUnit.cpp \
    Graphics/Factories/FactoryPixmap.cpp \
    Graphics/Factories/FactoryRes.cpp \
    Graphics/Factories/FactoryString.cpp \
    Graphics/Factories/FactoryUnits.cpp \
    Graphics/GameWindow.cpp \
    Graphics/GraphicsController/AGraphicsController.cpp \
    Graphics/GraphicsController/Calculations.cpp \
    Graphics/GraphicsController/CreateMap.cpp \
    Graphics/GraphicsController/EventsStructures.cpp \
    Graphics/GraphicsController/GraphicsController.cpp \
    Graphics/InformationWidgets/UnitInformation.cpp \
    Graphics/Map.cpp \
    Graphics/MenuTown/AWidgetTown.cpp \
    Graphics/MenuTown/InformWidget.cpp \
    Graphics/MenuTown/MenuAlreadyBuildTown.cpp \
    Graphics/MenuTown/MenuBuildTown.cpp \
    Graphics/MenuTown/MenuQueueTown.cpp \
    Graphics/MenuTown/MenuTown.cpp \
    Graphics/MenuTown/MenuTypeWorkTown.cpp \
    Graphics/MenuTown/WidgetTownBuilding.cpp \
    Graphics/MenuTown/WidgetTownUnit.cpp \
    Graphics/Menus/AMenuForUnit.cpp \
    Graphics/Menus/AMenuInWindow.cpp \
    Graphics/Menus/BottomMenu.cpp \
    Graphics/Menus/CitizenMenu.cpp \
    Graphics/Menus/UpperMenu.cpp \
    Graphics/Menus/WarriorMenu.cpp \
    Graphics/Menus/WorkerMenu.cpp \
    Graphics/Minimap.cpp \
    Graphics/Resources/Res.cpp \
    Graphics/Units/Unit.cpp \
    main.cpp

