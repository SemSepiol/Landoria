#include "TownBuildNeeds.h"
#include <random>

double TownBuildNeeds::get_build_need_production(TownBuildings type_building, int level) const
{
  return 30;
}

double TownBuildNeeds::get_build_need_production(Units unit) const
{
  return 30;
}

std::vector<std::pair<Resources, int>> TownBuildNeeds::get_build_need_res(TownBuildings type_building, int level) const
{
  srand(int(type_building) + level);
  std::vector<std::pair<Resources, int>> res;
  res.push_back({Resources::Iron, rand()%4 + 1});
  res.push_back({Resources::Stone, rand()%5});
  res.push_back({Resources::Horses, rand()%5});
  res.push_back({Resources::Coal, rand()%5});
  res.push_back({Resources::Aluminum, rand()%5});
  res.push_back({Resources::Oil, rand()%5});
  res.push_back({Resources::Uranium, rand()%5});
  return res;
}

std::vector<std::pair<Resources, int>> TownBuildNeeds::get_build_need_res(Units type_unit) const
{
  std::vector<std::pair<Resources, int>> res;
  res.push_back({Resources::Iron, 3});
  res.push_back({Resources::Stone, 3});
  res.push_back({Resources::Horses, 3});
  return res;
}
