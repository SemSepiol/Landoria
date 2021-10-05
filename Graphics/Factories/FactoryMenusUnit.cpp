#include "FactoryMenusUnit.h"

AMenuForUnit* FactoryMenusUnit::create_menu(QWidget* win, IGraphicsControllerMenuForUnit* graphics_controller, class Unit* unit, Cell* cell)
{
  switch (unit->what_unit_I())
  {
  case Units::Worker:
    return new WorkerMenu{win, graphics_controller, unit, cell};
  case Units::Citizen:
    return new CitizenMenu{win, graphics_controller, unit, cell};
  default:
    return new WarriorMenu{win, graphics_controller, unit, cell};
  }
}
