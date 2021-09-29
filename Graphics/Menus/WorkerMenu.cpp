#include "WorkerMenu.h"
#include <iostream>

WorkerMenu::WorkerMenu(QWidget* win, IPlayerForMenu* _player, class Unit* _unit)
  :AMenu(win, _player, _unit)
{}

int WorkerMenu::count_button() const
{
  return _count_button;
}

Event* WorkerMenu::what_butt(int num_butt)
{
  switch (num_butt)
  {
  case 0:
    return new Move_event{0,0};
  case 1:
    return new Slip_event{};
  default:
    throw std::runtime_error("No button with this number");
  }
}
