#include "Player.h"
#include <iostream>

Player::Player(IGameForPlayer* _game_controller)
  :game_controller{_game_controller}
{}

Player::~Player()
{
  for(size_t i{0}; i < my_units.size(); ++i)
    game_controller->graphics_controller()->del_unit(
          my_units[i].unit, my_units[i].cell_x, my_units[i].cell_y);
}

void Player::click_unit(class Unit* unit)
{
  PlayerUnit* my_unit = get_my_unit(unit);
  if (my_unit)
  {
    game_controller->graphics_controller()->do_menu_unit(unit);
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

void Player::menu_event(class Unit* unit, Event* event)
{
  std::cout << "ok" << std::endl;

  PlayerUnit* my_unit = get_my_unit(unit);
  if(my_unit)
  {
    if(event->event == Events::Move)
    {
      Move_event* move_event = static_cast<Move_event*>(event);
      move_unit_event(my_unit, move_event);
      return;
    }

    if(unit->what_unit_I() == Units::Citizen)
      event_for_citizen(my_unit, event);
    else
      set_event_to_unit(my_unit, event);
  }
  else
    throw std::runtime_error("set_event_to_unit: It's not my unit");

}

void Player::set_event_to_unit(PlayerUnit* my_unit, Event* event)
{
  my_unit->event.reset(event);
}


void Player::event_for_citizen(PlayerUnit* my_unit, Event* event)
{
  if(event->event == Events::Build)
  {
    Build_event* build_event = static_cast<Build_event*>(event);
    if(build_event->building == Buildings::Town)
    {
      game_controller->graphics_controller()->build(Buildings::Town, my_unit->cell_x, my_unit->cell_y);
    }
  }
  else
    set_event_to_unit(my_unit, event);
}

void Player::move_unit_event(PlayerUnit* my_unit, Move_event* event)
{
  game_controller->graphics_controller()->move_unit(
        my_unit->unit, my_unit->cell_x, my_unit->cell_y, event->cell_move_x, event->cell_move_y);
  my_unit->cell_x = event->cell_move_x;
  my_unit->cell_y = event->cell_move_y;
  my_unit->event.reset();
}

