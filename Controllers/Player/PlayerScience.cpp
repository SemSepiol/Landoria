#include "PlayerScience.h"

PlayerScience::PlayerScience()
{
  building.push_back(TownBuildings::Walls);
  best_units.push_back(Units::Citizen);
  best_units.push_back(Units::Worker);
  best_units.push_back(Units::Bowman);
  best_units.push_back(Units::Swordsman);
}


size_t PlayerScience::count_open_town_buildings() const
{
  return 1;
}

const std::vector<TownBuildings>& PlayerScience::get_open_town_buildings() const
{
  return building;
}

size_t PlayerScience::count_open_units() const
{
  return 4;
}

Units PlayerScience::get_open_unit(size_t ind) const
{
  return Units(ind);
}

size_t PlayerScience::count_best_open_units() const
{
  return 4;
}

const std::vector<Units>& PlayerScience::get_best_open_units() const
{
  return best_units;
}
