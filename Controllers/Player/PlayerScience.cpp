#include "PlayerScience.h"

PlayerScience::PlayerScience()
{
  building.push_back(TownBuildings::Walls);
  building.push_back(TownBuildings::Aqueduct);
  building.push_back(TownBuildings::Market);
  building.push_back(TownBuildings::PublicSchool);
  building.push_back(TownBuildings::University);
  building.push_back(TownBuildings::Bank);
  building.push_back(TownBuildings::Medical_Lab);
  building.push_back(TownBuildings::ResearchLab);
  building.push_back(TownBuildings::Factory);
  building.push_back(TownBuildings::Monument);
  building.push_back(TownBuildings::Shrine);
  building.push_back(TownBuildings::Windmill);
  building.push_back(TownBuildings::Museum);
  building.push_back(TownBuildings::Hospital);
  building.push_back(TownBuildings::Stadium);
  building.push_back(TownBuildings::Workshop);
  building.push_back(TownBuildings::Library);
  building.push_back(TownBuildings::OperaHouse);
  building.push_back(TownBuildings::StockExchange);
  building.push_back(TownBuildings::Zoo);

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
