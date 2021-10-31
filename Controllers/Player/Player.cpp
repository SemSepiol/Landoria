#include "Player.h"
#include <iostream>

Player::Player(IGameForPlayer* _game_controller, Countries _country)
  :game_controller{_game_controller}, country{_country},
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
  game_controller->graphics_controller()->update_res_inform(this);
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
    add_build(my_unit, build_event->building);
    my_unit->unit->set_movement(0);
  }
  else
  {
    stop_build(my_unit);
    set_event_to_unit(my_unit, event);
  }
}

void Player::move_unit_event(PlayerUnit* my_unit, MoveEvent* event)
{
  if(my_unit->unit->what_unit_I() == Units::Worker)
    stop_build(my_unit);

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

    if(is_military_unit(my_unit->unit->what_unit_I()))
      capture_cell(my_unit->pos);
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
    if(!unit)
      continue;

    if(unit->unit->get_movement() == 0)
      continue;

    class Worker* worker = static_cast<class Worker*>(unit->unit);
    class Building* building = unit_build[i].building;
    int phase = building->get_build_phase();
    building->set_build_phase(phase + worker->get_build_speed());

    if(building->get_build_phase() == building->get_end_build_phase())
    {
      add_res(unit_build[i].pos);
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
  Position pos = my_unit->pos;
  game_controller->graphics_controller()->centering_by_cell(pos);
  class Building* building = game_controller->
      graphics_controller()->build(Buildings::Town, pos);
  class Town* town = static_cast<class Town*>(building);
  my_towns.push_back(std::unique_ptr<PlayerTown>{new PlayerTown{town, this, pos}});
  del_unit(my_unit);

  auto map = game_controller->graphics_controller()->mapforfind();
  map->set_cell_country(pos, country);

  auto adjacent = map->adjacent_cells(pos);
  for(auto cell_pos : adjacent)
    if(map->get_cell_country(cell_pos) == Countries::Nothing)
      map->set_cell_country(cell_pos, country);
//  add_unit(Units::Worker, pos);
  game_controller->graphics_controller()->update_res_inform(this);
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
  unit->set_country(country);

  my_units.push_back(std::unique_ptr<PlayerUnit>{new PlayerUnit(unit, pos_cell)});

  if(type_unit == Units::Worker)
  {
    class Worker* worker = static_cast<class Worker*>(unit);
    worker->set_build_speed(UnitsCharaterichtics().get_worker_build_speed());
  }

  capture_cell(pos_cell);
}

int Player::get_gold_per_turn() const
{
  int count = 0;
  for(auto& town : my_towns)
    count += town->get_gold_per_turn();
  return count;
}

int Player::get_science_per_turn() const
{
  int count = 0;
  for(auto& town : my_towns)
    count += town->get_science_per_turn();
  return count;
}

PlayerRes* Player::get_player_res() const
{
  return player_res.get();
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

void Player::capture_cell(Position pos)
{
  auto map = game_controller->graphics_controller()->mapforfind();
  map->set_cell_country(pos, country);
}

void Player::add_build(PlayerUnit* unit, Buildings type_building)
{
  for(size_t i{0}; i < unit_build.size(); ++i)
    if(unit_build[i].pos == unit->pos)
    {
      if(unit_build[i].building->what_building_I() == type_building)
      {
        unit_build[i].unit = unit;
        if(unit->unit->get_movement() != 0)
        {
          class Worker* worker = static_cast<class Worker*>(unit->unit);
          unit_build[i].building->set_build_phase(unit_build[i].building->get_build_phase() + worker->get_build_speed());
        }
      }
      return;
    }

  class Building* building = game_controller->graphics_controller()->build(type_building, unit->pos);

  int end_phase = BuildingCharaterichtics().get_building_count_phase(building->what_building_I());
  building->set_end_build_phase(end_phase);

  if(unit->unit->get_movement() != 0)
  {
    class Worker* worker = static_cast<class Worker*>(unit->unit);
    building->set_build_phase(worker->get_build_speed());
  }
  unit_build.push_back({unit, building, unit->pos});
  if(building->get_end_build_phase() == building->get_build_phase())
  {
    unit->event.reset(new struct NoEvent());
    add_res(unit->pos);
  }
}

void Player::stop_build(PlayerUnit* unit)
{
  for(size_t i{0}; i < unit_build.size(); ++i)
    if(unit_build[i].unit == unit)
    {
      std::cout << "1243" << std::endl;
      unit_build[i].unit = nullptr;
      std::cout << unit_build[i].unit << std::endl;
      return;
    }
}

void Player::add_res(Position pos)
{
  IPlayerGraphicsController* gc = game_controller->graphics_controller();
  int count_res = gc->count_cell_resource(pos);
  if(count_res && gc->has_cell_building(pos))
  {
    Resources res = gc->cell_resource(pos);
    Buildings building = gc->cell_building(pos);

    if(building == Buildings::Town)
    {
      player_res->add_resource(res, count_res);
      return;
    }

    if(res == Resources::Aluminum || res == Resources::Gold ||
       res == Resources::Iron || res == Resources::Silver ||
       res == Resources::Uranium || res == Resources::Coal)
      if(building != Buildings::Mine)
        return;

    if(res == Resources::Stone)
      if(building != Buildings::Quarry)
        return;

    if(res == Resources::Horses)
      if(building != Buildings::Pasture)
        return;

    if(res == Resources::Oil)
      if(building != Buildings::OilWell)
        return;

    if(res == Resources::Fish)
      return;

    player_res->add_resource(res, count_res);
  }
  game_controller->graphics_controller()->update_res_inform(this);
}

void Player::del_res(Position pos)
{
  IPlayerGraphicsController* gc = game_controller->graphics_controller();
  int count_res = gc->count_cell_resource(pos);
  if(count_res && gc->has_cell_building(pos))
  {
    Resources res = gc->cell_resource(pos);
    Buildings building = gc->cell_building(pos);

    if(building == Buildings::Town)
    {
      player_res->del_resource(res, count_res);
      return;
    }

    if(res == Resources::Aluminum || res == Resources::Gold ||
       res == Resources::Iron || res == Resources::Silver ||
       res == Resources::Uranium || res == Resources::Coal)
      if(building != Buildings::Mine)
        return;

    if(res == Resources::Stone)
      if(building != Buildings::Quarry)
        return;

    if(res == Resources::Horses)
      if(building != Buildings::Pasture)
        return;

    if(res == Resources::Oil)
      if(building != Buildings::OilWell)
        return;

    if(res == Resources::Fish)
      return;

    player_res->del_resource(res, count_res);
  }
  game_controller->graphics_controller()->update_res_inform(this);
}

bool Player::is_military_unit(Units type_unit)
{
  if(type_unit == Units::Worker || type_unit == Units::Citizen)
    return false;
  return true;
}
