#include "MenuStartGraphicsController.h"
#include <iostream>

MenuStartGraphicsController::MenuStartGraphicsController(IGraphicsController* _graphics_controller)
  :graphics_controller{_graphics_controller}
{}

void MenuStartGraphicsController::do_start_menu()
{
  menu_start.reset(new StartMenu(this));
  menu_start->set_geometry({0,0}, graphics_controller->get_size_win());
  menu_start->hide();
  menu_start->show();
}

QWidget* MenuStartGraphicsController::window() const
{
  return graphics_controller->get_game_window();
}

void MenuStartGraphicsController::start_game()
{
  menu_start.reset();
  graphics_controller->start_game();
}
