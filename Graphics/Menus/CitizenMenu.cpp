#include "CitizenMenu.h"
#include <iostream>

CitizenMenu::CitizenMenu(QWidget* win, IPlayerForMenu* _player, class Unit* _unit)
  :AMenu(win, _player, _unit)
{}

int CitizenMenu::count_button() const
{
  return _count_button;
}

Event* CitizenMenu::what_butt(int num_butt)
{
  switch (num_butt)
  {
  case 0:
    return new Build_event{Buildings::Town};
  case 1:
    return new Move_event{0,0};
  case 2:
    return new Slip_event{};
  default:
    throw std::runtime_error("No button with this number");
  }
}
