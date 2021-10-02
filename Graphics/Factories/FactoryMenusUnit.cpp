#include "FactoryMenusUnit.h"

AMenuForUnit* FactoryMenusUnit::create_menu(QWidget* win, IGraphicsControllerMenuForUnit* graphics_controller, class Unit* unit)
{
  switch (unit->what_unit_I())
  {
  case Units::Worker:
    return new WorkerMenu{win, graphics_controller, unit};
  case Units::Citizen:
    return new CitizenMenu{win, graphics_controller, unit};
  default:
    throw std::runtime_error("create_menu: there is no menu for this unit");
  }
}
