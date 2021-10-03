#include "WorkerMenu.h"
#include <iostream>

WorkerMenu::WorkerMenu(QWidget* win, IGraphicsControllerMenuForUnit* _graphics_controller,
                       class Unit* _unit, Cell* _cell)
  :AMenuForUnit(win, _graphics_controller, _unit, _cell)
{
  buttons.push_back(new MoveEvent{0,0});
  buttons.push_back(new SlipEvent{});
}
