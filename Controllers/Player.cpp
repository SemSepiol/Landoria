#include "Player.h"
#include <iostream>

Player::Player(IGameForPlayer* _game_controller)
  :game_controller{_game_controller}
{}

Player::~Player()
{
  for(size_t i{0}; i < my_units.size(); ++i)
    game_controller->graphics_controller()->del_unit(
          my_units[i].unit, my_units[i].pos);
}

void Player::click_unit(class Unit* unit)
{
  PlayerUnit* my_unit = get_my_unit(unit);
  if (my_unit)
    unit_move(my_unit);
}

void Player::click_town(class Town* town)
{
  PlayerTown* my_town = get_my_town(town);
  if (my_town)
  {
    game_controller->graphics_controller()->do_menu_town(town);
  }
}

void Player::set_initial_units(Position initial_cell)
{
  add_unit(Units::Worker, initial_cell);
  add_unit(Units::Citizen, initial_cell);
  add_unit(Units::Bowman, initial_cell);
  add_unit(Units::Swordsman, initial_cell);
}

PlayerUnit* Player::get_my_unit(class Unit* unit)
{
  for(size_t i{0}; i < my_units.size(); ++i)
    if(my_units[i].unit == unit)
      return &my_units[i];
  return nullptr;
}

PlayerTown* Player::get_my_town(class Town* town)
{
  for(size_t i{0}; i < my_towns.size(); ++i)
    if(my_towns[i].town == town)
      return &my_towns[i];
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

void Player::start_move()
{
  for(size_t i{0}; i < my_units.size(); ++i)
    if(my_units[i].event->event == Events::NoEvent)
    {
      unit_move(&my_units[i]);
      return;
    }
}

void Player::end_move()
{

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
    {
      class Building* building = game_controller->
          graphics_controller()->build(Buildings::Town, my_unit->pos);
      class Town* town = static_cast<class Town*>(building);
      add_town(town, {build_event->pos_cell});
    }
  }
  else
    set_event_to_unit(my_unit, event);
}

void Player::event_for_worker(PlayerUnit* my_unit, Event* event)
{
  if(event->event == Events::Build)
  {
    BuildEvent* build_event = static_cast<BuildEvent*>(event);
    game_controller->graphics_controller()->build(build_event->building, my_unit->pos);
  }
  else
    set_event_to_unit(my_unit, event);
}

void Player::move_unit_event(PlayerUnit* my_unit, MoveEvent* event)
{
  game_controller->graphics_controller()->move_unit(
        my_unit->unit, my_unit->pos, event->cell_move);
  my_unit->pos = event->cell_move;
  my_unit->event.reset();
}

void Player::add_town(class Town* town, Position pos)
{
  my_towns.push_back(PlayerTown{town, pos});
}

void Player::add_unit(Units type_unit, Position pos_cell)
{
  UnitsCharaterichtics unitcharaterichtics;
  int max_health = unitcharaterichtics.get_unit_max_health(type_unit);
  int max_movement = unitcharaterichtics.get_unit_max_movement(type_unit);
  class Unit* unit = game_controller->graphics_controller()->add_unit(
        type_unit, pos_cell, max_health, max_movement);

  my_units.push_back({unit, pos_cell});
}

void Player::unit_move(PlayerUnit* unit)
{
  game_controller->graphics_controller()->centering_by_cell(unit->pos);
  game_controller->graphics_controller()->do_menu_unit(unit->unit, unit->pos);
  game_controller->graphics_controller()->highlight_unit(unit->unit, unit->pos);
}
