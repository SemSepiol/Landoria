#ifndef FACTORYMENUSUNIT_H
#define FACTORYMENUSUNIT_H

#include <QWidget>

#include "../Menus/AMenuForUnit.h"
#include "../Menus/CitizenMenu.h"
#include "../Menus/WarriorMenu.h"
#include "../Menus/WorkerMenu.h"
#include "../Units/Unit.h"
#include "../../Controllers/Player/IPlayer.h"
#include "../../IObject.h"


class FactoryMenusUnit : public IObject
{
public:
  AMenuForUnit* create_menu(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
                            PlayerUnit* unit, Cell* cell);
};

#endif // FACTORYMENUSUNIT_H
