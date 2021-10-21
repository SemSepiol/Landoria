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
