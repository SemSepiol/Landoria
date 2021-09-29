#include "Player.h"
#include <iostream>

Player::Player(IGameForPlayer* _game_controller)
  :game_controller{_game_controller}
{}

Player::~Player()
{
  for(PlayerUnit unit : my_units)
    game_controller->graphics_controller()->del_unit(unit.unit, unit.cell_x, unit.cell_y);
}

void Player::click_unit(class Unit* unit)
{
  PlayerUnit* my_unit = get_my_unit(unit);
  if (my_unit)
  {
    game_controller->graphics_controller()->do_menu_unit(this, unit);
  }
}

void Player::set_initial_units(size_t initial_cell_x, size_t initial_cell_y)
{
  class Unit* unit = game_controller->graphics_controller()->add_unit(Units::Citizen, initial_cell_x, initial_cell_y);
  my_units.push_back({initial_cell_x, initial_cell_y, unit});
}

PlayerUnit* Player::get_my_unit(class Unit* unit)
{
  for(size_t i{0}; i < my_units.size(); ++i)
    if(my_units[i].unit == unit)
      return &my_units[i];
  return nullptr;
}

void Player::menu_event(Event* event, class Unit* unit)
{
  std::cout << "ok" << std::endl;
}
