#ifndef FACTORYMENUSUNIT_H
#define FACTORYMENUSUNIT_H

#include <QWidget>

#include "../Menus/MenuUnit/AMenuForUnit.h"
#include "../Menus/MenuUnit/CitizenMenu.h"
#include "../Menus/MenuUnit/WarriorMenu.h"
#include "../Menus/MenuUnit/WorkerMenu.h"
#include "../../Controllers/Player/IPlayer.h"
#include "../../IObject.h"


class FactoryMenusUnit : public IObject
{
public:
  AMenuForUnit* create_menu(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
                            PlayerUnit* unit, Cell* cell);
};

#endif // FACTORYMENUSUNIT_H
