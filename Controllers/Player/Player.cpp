#include "Player.h"
#include <iostream>

Player::Player(IGameForPlayer* _game_controller)
  :game_controller{_game_controller},
    player_map{new PlayerMap({_game_controller->count_cell_x(), _game_controller->count_cell_y()})},
    player_res{new PlayerRes()}, _player_science{new PlayerScience()}
{}

Player::~Player()
{
  for(size_t i{0}; i < my_units.size(); ++i)
    del_unit(my_units[i].get());
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
    game_controller->graphics_controller()->centering_by_cell(my_town->position_town());
    game_controller->graphics_controller()->do_menu_town(this, my_town);
  }
}

void Player::set_initial_units(Position initial_cell)
{
//  add_unit(Units::Worker, initial_cell);
//  add_unit(Units::Worker, initial_cell);
  add_unit(Units::Citizen, initial_cell);
//  build_town(&my_units[0]);
//  click_town(my_towns[0]->town());
//  add_unit(Units::Bowman, initial_cell);
//  add_unit(Units::Swordsman, initial_cell);
  set_units_vision(true);
}

PlayerUnit* Player::get_my_unit(class Unit* unit)
{
  for(size_t i{0}; i < my_units.size(); ++i)
    if(my_units[i]->unit == unit)
      return my_units[i].get();
  return nullptr;
}

size_t Player::get_ind_my_unit(PlayerUnit* unit)
{
  for(size_t i{0}; i < my_units.size(); ++i)
    if(my_units[i].get() == unit)
      return i;
  return my_units.size();
}

PlayerTown* Player::get_my_town(class Town* town)
{
  for(size_t i{0}; i < my_towns.size(); ++i)
    if(my_towns[i]->town() == town)
      return my_towns[i].get();
  return nullptr;
}

void Player::menu_event(class Unit* unit, Event* event)
{
  //  std::cout << "menu_event_ok" << std::endl;

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

bool Player::is_finish()
{

  do_events_unit();
  do_build_towns();
  for(size_t i{0}; i < my_units.size(); ++i)
  {
    if(my_units[i]->event->event != Events::NoEvent)
      continue;
    if(my_units[i]->unit->get_movement() == 0)
      continue;
    return false;
  }

  for(size_t i{0}; i < my_towns.size(); ++i)
    if(my_towns[i]->get_build_queue().size() == 0)
      return false;


  return true;
}

void Player::start_move()
{
  for(size_t i{0}; i < my_units.size(); ++i)
    if(my_units[i]->event->event == Events::NoEvent and my_units[i]->unit->get_movement() != 0)
    {
      unit_move(my_units[i].get());
      return;
    }
  for(size_t i{0}; i < my_towns.size(); ++i)
    if(my_towns[i]->get_build_queue().size() == 0)
    {
      click_town(my_towns[i].get()->town());
      return;
    }
}

void Player::end_move()
{
  set_movement_to_max_unit();
  set_new_move_to_towns();
}

void Player::draw_my_map()
{
  game_controller->graphics_controller()->draw_playermap(player_map.get());
}

PlayerScience* Player::player_science() const
{
  return _player_science.get();
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
    if(build_event->building != Buildings::Town)
      std::runtime_error("Citizen can build only town");

    build_town(my_unit);
  }
  else
    set_event_to_unit(my_unit, event);
}

void Player::event_for_worker(PlayerUnit* my_unit, Event* event)
{
  if(event->event == Events::Build)
  {
    BuildEvent* build_event = static_cast<BuildEvent*>(event);
    my_unit->event.reset(event);

    class Building* building = game_controller->graphics_controller()->build(build_event->building, my_unit->pos);

    int end_phase = BuildingCharaterichtics().get_building_count_phase(building->what_building_I());
    building->set_end_build_phase(end_phase);

    if(my_unit->unit->get_movement() != 0)
    {
      class Worker* worker = static_cast<class Worker*>(my_unit->unit);
      building->set_build_phase(worker->get_build_speed());
    }

    unit_build.push_back({my_unit, building});
    my_unit->unit->set_movement(0);

    if(building->get_end_build_phase() == building->get_build_phase())
      my_unit->event.reset(new struct NoEvent());
  }
  else
    set_event_to_unit(my_unit, event);
}

void Player::move_unit_event(PlayerUnit* my_unit, MoveEvent* event)
{

  IMapForFind* map = game_controller->graphics_controller()->mapforfind();
  OneMove move = FindUnitWay().get_first_move(my_unit->unit, map, my_unit->pos, event->cell_move);

  for(size_t i{1}; i < move.minimove.size(); ++i)
  {
    int unit_movement = my_unit->unit->get_movement();
    if(unit_movement == 0)
      break;
    my_unit->unit->set_movement(unit_movement - 1);

    set_units_vision(false);

    Position move_cell = move.minimove[i];
    game_controller->graphics_controller()->move_unit(
          my_unit->unit, my_unit->pos, move_cell);
    my_unit->pos = move_cell;

    set_units_vision(true);
  }


  if(my_unit->pos == event->cell_move || my_unit->unit->get_movement() != 0)
  {
    delete event;
    my_unit->event.reset(new struct NoEvent());
  }
  else
  {
    my_unit->event.reset(event);
  }

  draw_my_map();
}

void Player::set_units_vision(bool vision)
{
  for(size_t i{0}; i < my_units.size(); ++i)
  {
    IMapForFind* map = game_controller->graphics_controller()->mapforfind();
    std::vector<Position> unit_vision =
        FindUnitVision().unit_vision(my_units[i]->unit, my_units[i]->pos, map);

    for(Position pos : unit_vision)
    {
      if(vision)
        player_map->set_show_cell(pos);
      else
        player_map->set_notvisible_cell(pos);
    }
  }
}

void Player::set_movement_to_max_unit()
{
  for(size_t i{0}; i < my_units.size(); ++i)
    my_units[i]->unit->set_movement(my_units[i]->unit->get_max_movement());
}

void Player::set_new_move_to_towns()
{
  for(size_t i{0}; i < my_towns.size(); ++i)
    my_towns[i]->new_move();
}

void Player::do_events_unit()
{
  for(size_t i{0}; i < my_units.size(); ++i)
  {
    if(my_units[i]->event->event == Events::Move)
    {
      MoveEvent* move_event = static_cast<MoveEvent*>(my_units[i]->event->copy());
      move_unit_event(my_units[i].get(), move_event);
    }
  }

  for(size_t i{0}; i < unit_build.size(); ++i)
  {
    PlayerUnit* unit = unit_build[i].unit;
    if(unit->unit->get_movement() == 0)
      continue;

    class Worker* worker = static_cast<class Worker*>(unit->unit);
    class Building* building = unit_build[i].building;
    int phase = building->get_build_phase();
    building->set_build_phase(phase + worker->get_build_speed());

    if(building->get_build_phase() == building->get_end_build_phase())
    {
      unit_build.erase(unit_build.begin() + i);
      i--;
      unit->event.reset(new struct NoEvent());
    }
    unit->unit->set_movement(0);
  }
}

void Player::do_build_towns()
{
  for(size_t i{0}; i < my_towns.size(); ++i)
    my_towns[i]->move_build();
}

void Player::build_town(PlayerUnit* my_unit)
{
  game_controller->graphics_controller()->centering_by_cell(my_unit->pos);
  class Building* building = game_controller->
      graphics_controller()->build(Buildings::Town, my_unit->pos);
  class Town* town = static_cast<class Town*>(building);
  my_towns.push_back(std::unique_ptr<PlayerTown>{new PlayerTown{town, my_unit->pos}});
  del_unit(my_unit);
}

void Player::add_unit(Units type_unit, Position pos_cell)
{
  UnitsCharaterichtics unitcharaterichtics;
  int max_health = unitcharaterichtics.get_unit_max_health(type_unit);
  int max_movement = unitcharaterichtics.get_unit_max_movement(type_unit);
  int vision = unitcharaterichtics.get_unit_vision(type_unit);
  class Unit* unit = game_controller->graphics_controller()->add_unit(type_unit, pos_cell);

  unit->set_max_health(max_health);
  unit->set_health(max_health);
  unit->set_max_movement(max_movement);
  unit->set_movement(max_movement);
  unit->set_vision(vision);

  my_units.push_back(std::unique_ptr<PlayerUnit>{new PlayerUnit(unit, pos_cell)});

  if(type_unit == Units::Worker)
  {
    class Worker* worker = static_cast<class Worker*>(unit);
    worker->set_build_speed(UnitsCharaterichtics().get_worker_build_speed());
  }
}

void Player::del_unit(PlayerUnit* unit)
{
  game_controller->graphics_controller()->del_unit(unit->unit, unit->pos);
  my_units.erase(my_units.begin() + get_ind_my_unit(unit));
}

void Player::unit_move(PlayerUnit* unit)
{
  game_controller->graphics_controller()->centering_by_cell(unit->pos);
  game_controller->graphics_controller()->do_menu_unit(unit);
  game_controller->graphics_controller()->highlight_unit(unit->unit, unit->pos);
}
