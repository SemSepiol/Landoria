#include "TownBuildNeeds.h"

int TownBuildNeeds::get_build_need_production(TownBuildings type_building, int level) const
{
  return 30;
}

int TownBuildNeeds::get_build_need_production(Units unit) const
{
  return 30;
}

std::vector<std::pair<Resources, int>> TownBuildNeeds::get_build_need_res(TownBuildings type_building, int level) const
{
  std::vector<std::pair<Resources, int>> res;
  res.push_back({Resources::Iron, 3});
  res.push_back({Resources::Stone, 3});
  res.push_back({Resources::Horses, 3});
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
