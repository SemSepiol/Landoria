#include "MenuTown.h"
#include "iostream"

MenuTown::MenuTown(IMenuTownPlayer* player, ITownMenuGraphicsController* graphics_controller,
                   PlayerTown* town)
  : _player{player}, _graphics_controller{graphics_controller}, _town{town},
    menu_build_town{new MenuBuildTown(this)}, menu_type_work_town{new MenuTypeWorkTown{this}}
{}

void MenuTown::set_geometry(QPoint _pos, Size _size)
{
  pos = _pos;
  size = _size;
  set_geometry_menu_build();
  set_geometry_menu_selectwork();
}

void MenuTown::start()
{
  menu_build_town->hide();
  menu_build_town->show();
  menu_type_work_town->hide();
  menu_type_work_town->show();
}

ITownMenuGraphicsController* MenuTown::graphics_controller() const
{
  return _graphics_controller;
}

QWidget* MenuTown::window() const
{
  return _graphics_controller->window();
}

PlayerTown* MenuTown::town() const
{
  return _town;
}

IMenuTownPlayer* MenuTown::player() const
{
  return _player;
}

void MenuTown::delete_townmenu()
{
  _graphics_controller->delete_townmenu();
}

void MenuTown::open_menu_build()
{
  if(menu_build_town.get())
    return;
  std::cout << "123" << std::endl;
  menu_build_town.reset(new MenuBuildTown{this});
  set_geometry_menu_build();
  menu_build_town->hide();
  menu_build_town->show();
}

void MenuTown::open_menu_alreadybuild()
{
  close_menu_build();
}

void MenuTown::close_menu_build()
{
  menu_build_town.reset();
}

void MenuTown::close_menu_alreadybuild()
{
  menu_type_work_town.reset();
}

void MenuTown::set_geometry_menu_build()
{
  menu_build_town->set_geometry(pos + QPoint{size.width/3, 0}, {size.width/3, size.height});
}

void MenuTown::set_geometry_menu_selectwork()
{
  Size size_menu_type_work{size.width/3,
        size.height/10*int(menu_type_work_town->count_button())};

  QPoint pos_menu_type_work{pos.x(),
        pos.y() + (size.height - size_menu_type_work.height)/2};

  menu_type_work_town->set_geometry(pos_menu_type_work, size_menu_type_work);
}
