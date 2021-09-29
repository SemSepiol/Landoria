#ifndef FACTORYMENUSUNIT_H
#define FACTORYMENUSUNIT_H
#include <QWidget>

#include "../../IObject.h"
#include "../../Controllers/IPlayer.h"
#include "../Units/Unit.h"

#include "../Menus/AMenu.h"
#include "../Menus/WorkerMenu.h"
#include "../Menus/CitizenMenu.h"


class FactoryMenusUnit : public IObject
{
public:
  AMenu* create_menu(QWidget* win, IPlayerForMenu* player, class Unit* unit);
};

#endif // FACTORYMENUSUNIT_H
