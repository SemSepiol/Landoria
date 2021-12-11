#include "FactoryMenusUnit.h"

AMenuForUnit* FactoryMenusUnit::create_menu(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
                                            PlayerUnit* unit, Cell* cell)
{
  switch (unit->unit->what_unit_I())
  {
  case Units::Worker:
    return new WorkerMenu{win, graphics_controller, unit, cell};
  case Units::Citizen:
    return new CitizenMenu{win, graphics_controller, unit, cell};
  default:
    return new WarriorMenu{win, graphics_controller, unit, cell};
  }
}
