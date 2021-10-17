#include "PlayerScience.h"

PlayerScience::PlayerScience()
{}


size_t PlayerScience::count_open_town_buildings() const
{
  return 1;
}

TownBuildings PlayerScience::get_open_town_building(size_t ind) const
{
  return TownBuildings(ind);
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

Units PlayerScience::get_best_open_unit(size_t ind) const
{
  return Units(ind);
}
