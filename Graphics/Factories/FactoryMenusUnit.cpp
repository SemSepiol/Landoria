#include "FactoryMenusUnit.h"

AMenuForUnit* FactoryMenusUnit::create_menu(QWidget* win, IPlayerForMenu* player, class Unit* unit)
{
  switch (unit->what_unit_I())
  {
  case Units::Worker:
    return new WorkerMenu{win, player, unit};
  case Units::Citizen:
    return new CitizenMenu{win, player, unit};
  default:
    throw std::runtime_error("create_menu: there is no menu for this unit");
  }
}
