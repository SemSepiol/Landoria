#include "Player.h"
#include <iostream>

Player::Player(IGameForPlayer* _game_controller)
  :game_controller{_game_controller}
{}

void Player::click_unit(class Unit* unit)
{
  PlayerUnit* my_unit = get_my_unit(unit);
  if (my_unit)
    game_controller->graphics_controller()->move_unit(my_unit->unit, my_unit->cell_x, my_unit->cell_y,
                                                      my_unit->cell_x+1, my_unit->cell_y+1);
  my_unit->cell_x++;
  my_unit->cell_y++;
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
