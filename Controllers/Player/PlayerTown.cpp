#include "PlayerTown.h"

PlayerTown::PlayerTown(class Town* town, Position pos)
  :_town{town}, _pos{pos}
{}

Position PlayerTown::position_town() const
{
  return _pos;
}

class Town* PlayerTown::town() const
{
  return _town.get();
}

size_t PlayerTown::count_town_buildings() const
{
  return buildings.size();
}

const std::vector<TownBuildings>& PlayerTown::get_town_buildings() const
{
  return buildings;
}

void PlayerTown::add_town_building(TownBuildings town_building)
{
  buildings.push_back(town_building);
}

void PlayerTown::add_queue_build(Units type_unit)
{
  build_queue.push_back({type_unit});
}

void PlayerTown::add_queue_build(TownBuildings type_building)
{
  build_queue.push_back({type_building});
}

void PlayerTown::set_build(Units type_unit)
{
  build_queue.clear();
  build_queue.push_back(type_unit);
}

void PlayerTown::set_build(TownBuildings type_building)
{
  build_queue.clear();
  build_queue.push_back(type_building);
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
  return TownBuildNeeds().get_build_need_production(type_building);
}

int PlayerTown::get_build_need_production(Units type_unit)
{
  return TownBuildNeeds().get_build_need_production(type_unit);
}

const std::vector<BuildInTown>& PlayerTown::get_build_queue() const
{
  return build_queue;
}

int PlayerTown::get_production() const
{
  return production;
}

int PlayerTown::get_surplus_production() const
{
  return surplus_production;
}
