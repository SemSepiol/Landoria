#include "PlayerTown.h"
#include <iostream>

PlayerTown::PlayerTown(class Town* town, ITownPlayer* _player, Position pos)
  :_town{town}, player{_player}, _pos{pos}
{
  gold_per_turn = 1;
  science_per_turn = 1;
}

Position PlayerTown::position_town() const
{
  return _pos;
}

class Town* PlayerTown::town() const
{
  return _town;
}

void PlayerTown::move_build()
{
  if(build_queue.size() == 0)
    return;

  if(build_in_this_move)
    remains_production = build_queue[0]->build(remains_production);
  else
    remains_production = build_queue[0]->build(get_production() + remains_production);

  build_in_this_move = true;

  if(build_queue[0]->need_production == 0)
  {
    if(build_queue[0]->type_build == BuildInTown::Unit)
    {
      player->add_unit(build_queue[0]->unit, _pos);
      del_build(build_queue[0]);
    }
    else
    {
      build_queue[0]->level++;
      build_queue[0]->build_next_level();
    }

    build_queue.erase(build_queue.begin());
    move_build();
  }
}

void PlayerTown::new_move()
{
  build_in_this_move = false;
}

int PlayerTown::get_gold_per_turn() const
{
  return gold_per_turn;
}

int PlayerTown::get_science_per_turn() const
{
  return science_per_turn;
}

size_t PlayerTown::count_town_buildings() const
{
  return build_in_town.size();
}

std::vector<TownBuildings> PlayerTown::get_building_already_build() const
{
  std::vector<TownBuildings> building_in_town;
  for(size_t i{0}; i < build_in_town.size(); ++i)
    if(build_in_town[i]->type_build == BuildInTown::Building)
      if(build_in_town[i]->need_production == 0 || build_in_town[i]->level != 0)
        building_in_town.push_back(build_in_town[i]->building);
  return building_in_town;
}

std::vector<TownBuildings> PlayerTown::get_queue_buildings() const
{
  std::vector<TownBuildings> building_queue;
  for(auto build : build_queue)
    if(build->type_build == BuildInTown::Building)
      building_queue.push_back(build->building);
  return building_queue;
}

void PlayerTown::add_queue_build(Units type_unit)
{
  build_in_town.push_back(std::unique_ptr<BuildInTown>{new BuildInTown(type_unit)});
  build_queue.push_back(build_in_town[build_in_town.size() - 1].get());
}

void PlayerTown::add_queue_build(TownBuildings type_building)
{

  for(size_t i{0}; i < build_in_town.size(); ++i)
    if(build_in_town[i]->type_build == BuildInTown::Building)
      if(build_in_town[i]->building == type_building)
      {
        build_queue.push_back(build_in_town[i].get());
        return;
      }

  build_in_town.push_back(std::unique_ptr<BuildInTown>{new BuildInTown(type_building)});
  build_queue.push_back(build_in_town[build_in_town.size() - 1].get());
}

void PlayerTown::set_build(Units type_unit)
{
  build_queue.clear();
  add_queue_build(type_unit);
}

void PlayerTown::set_build(TownBuildings type_building)
{
  build_queue.clear();
  add_queue_build(type_building);
}

void PlayerTown::del_build(size_t i)
{
  build_queue.erase(build_queue.begin() + i);
}

void PlayerTown::move_up_build(size_t i)
{
  if(i == 0)
    return;
  std::swap(build_queue[i], build_queue[i-1]);
}

void PlayerTown::move_down_build(size_t i)
{
  if(i+1 >= build_queue.size())
    return;
  std::swap(build_queue[i], build_queue[i+1]);
}

size_t PlayerTown::max_build_in_queue()
{
  return _max_build_in_queue;
}

int PlayerTown::get_build_need_production(TownBuildings type_building)
{
  for(size_t i{0}; i < build_in_town.size(); ++i)
    if(build_in_town[i]->type_build == BuildInTown::Building)
      if(build_in_town[i]->building == type_building)
        return build_in_town[i]->need_production;
  return TownBuildNeeds().get_build_need_production(type_building, 1);
}

int PlayerTown::get_build_need_production(Units type_unit)
{
  for(size_t i{0}; i < build_in_town.size(); ++i)
    if(build_in_town[i]->type_build == BuildInTown::Unit)
      if(build_in_town[i]->unit == type_unit)
        return build_in_town[i]->need_production;
  return TownBuildNeeds().get_build_need_production(type_unit);
}

int PlayerTown::get_level_build(TownBuildings type_building)
{
  for(size_t i{0}; i < build_in_town.size(); ++i)
    if(build_in_town[i]->type_build == BuildInTown::Building)
      if(build_in_town[i]->building == type_building)
        return build_in_town[i]->level;
  return 0;
}

const std::vector<BuildInTown*>& PlayerTown::get_build_queue() const
{
  return build_queue;
}

int PlayerTown::get_production() const
{
  return production;
}

int PlayerTown::get_remains_production() const
{
  return remains_production;
}

void PlayerTown::del_build(BuildInTown* build)
{
  for(size_t i{0}; i < build_in_town.size(); ++i)
    if(build_in_town[i].get() == build)
      build_in_town.erase(build_in_town.begin() + i);
}
