#ifndef BUILDINTOWN_H
#define BUILDINTOWN_H

#include "../TownBuildings.h"
#include "../TownBuildNeeds.h"


struct BuildInTown
{
  enum TypeBuild{
    Unit,
    Building
  };

  TypeBuild type_build;
  TownBuildings building;
  int level = 0;
  Units unit;
  double need_production;

  BuildInTown(Units type_unit)
    :type_build{TypeBuild::Unit}, unit{type_unit}
  {
    need_production = TownBuildNeeds().get_build_need_production(type_unit);
  }

  BuildInTown(TownBuildings type_building)
    :type_build{TypeBuild::Building}, building{type_building}
  {
    need_production = TownBuildNeeds().get_build_need_production(type_building, 1);
  }

  //возвращает остаток
  double build(double town_production);

  void build_next_level();
};

#endif // BUILDINTOWN_H
