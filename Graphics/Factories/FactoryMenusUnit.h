#ifndef FACTORYMENUSUNIT_H
#define FACTORYMENUSUNIT_H
#include <QWidget>

#include "../../IObject.h"
#include "../../Controllers/IPlayer.h"
#include "../Units/Unit.h"

#include "../Menus/AMenuForUnit.h"
#include "../Menus/WorkerMenu.h"
#include "../Menus/CitizenMenu.h"
#include "../Menus/WarriorMenu.h"


class FactoryMenusUnit : public IObject
{
public:
  AMenuForUnit* create_menu(QWidget* win, IGraphicsControllerMenuForUnit* graphics_controller,
                            class Unit* unit, Cell* cell);
};

#endif // FACTORYMENUSUNIT_H
