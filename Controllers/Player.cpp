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
    game_controller->graphics_controller()->do_menu_unit(unit, my_unit->cell_x, my_unit->cell_y);
  }
}

void Player::set_initial_units(size_t initial_cell_x, size_t initial_cell_y)
{
  add_unit(Units::Worker, initial_cell_x, initial_cell_y);
  add_unit(Units::Citizen, initial_cell_x, initial_cell_y);
  add_unit(Units::Bowman, initial_cell_x, initial_cell_y);
  add_unit(Units::Swordsman, initial_cell_x, initial_cell_y);
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
  std::cout << "menu_event_ok" << std::endl;

  PlayerUnit* my_unit = get_my_unit(unit);
  if(my_unit)
  {
    if(event->event == Events::Move)
    {
      MoveEvent* move_event = static_cast<MoveEvent*>(event);
      move_unit_event(my_unit, move_event);
      return;
    }

    if(unit->what_unit_I() == Units::Citizen)
      event_for_citizen(my_unit, event);
    else if(unit->what_unit_I() == Units::Worker)
      event_for_worker(my_unit, event);
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
    BuildEvent* build_event = static_cast<BuildEvent*>(event);

    if(build_event->building == Buildings::Town)
      game_controller->graphics_controller()->build(Buildings::Town,
                                                    my_unit->cell_x, my_unit->cell_y);
  }
  else
    set_event_to_unit(my_unit, event);
}

void Player::event_for_worker(PlayerUnit* my_unit, Event* event)
{
  if(event->event == Events::Build)
  {
    BuildEvent* build_event = static_cast<BuildEvent*>(event);
    game_controller->graphics_controller()->build(build_event->building,
                                                  my_unit->cell_x, my_unit->cell_y);
  }
  else
    set_event_to_unit(my_unit, event);
}

void Player::move_unit_event(PlayerUnit* my_unit, MoveEvent* event)
{
  game_controller->graphics_controller()->move_unit(
        my_unit->unit, my_unit->cell_x, my_unit->cell_y, event->cell_move_x, event->cell_move_y);
  my_unit->cell_x = event->cell_move_x;
  my_unit->cell_y = event->cell_move_y;
  my_unit->event.reset();
}

void Player::add_unit(Units type_unit, size_t position_x, size_t position_y)
{
  UnitsCharaterichtics unitcharaterichtics;
  int max_health = unitcharaterichtics.get_unit_max_health(type_unit);
  int max_movement = unitcharaterichtics.get_unit_max_movement(type_unit);
  class Unit* unit = game_controller->graphics_controller()->add_unit(
        type_unit, position_x, position_y, max_health, max_movement);

  my_units.push_back({position_x, position_y, unit});
}

