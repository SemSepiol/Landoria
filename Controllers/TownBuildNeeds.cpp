#include "TownBuildNeeds.h"

int TownBuildNeeds::get_build_need_production(TownBuildings type_building) const
{
  return 30;
}

int TownBuildNeeds::get_build_need_production(Units unit) const
{
  return 30;
}
