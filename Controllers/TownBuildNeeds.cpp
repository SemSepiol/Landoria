#include "TownBuildNeeds.h"

int TownBuildNeeds::get_build_need_production(TownBuildings type_building) const
{
  return 30;
}

int TownBuildNeeds::get_build_need_production(Units unit) const
{
  return 30;
}

std::vector<std::pair<Resources, int>> TownBuildNeeds::get_build_need_res(TownBuildings type_building) const
{
  std::vector<std::pair<Resources, int>> res;
  res.push_back({Iron, 3});
  res.push_back({Stone, 3});
  res.push_back({Horses, 3});
  return res;
}

std::vector<std::pair<Resources, int>> TownBuildNeeds::get_build_need_res(Units type_unit) const
{
  std::vector<std::pair<Resources, int>> res;
  res.push_back({Iron, 3});
  res.push_back({Stone, 3});
  res.push_back({Horses, 3});
  return res;
}
