#include "MenuTown.h"

MenuTown::MenuTown(ITownMenuGraphicsController* _graphics_controller, PlayerTown* _town)
  :menu_build_town{new MenuBuildTown(_graphics_controller, _town)}
{}

void MenuTown::set_geometry(QPoint pos, Size size)
{
  menu_build_town->set_geometry(pos, size);
}

void MenuTown::start()
{
  menu_build_town->hide();
  menu_build_town->show();
}
