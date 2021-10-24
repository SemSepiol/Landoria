#ifndef PLAYERTOWN_H
#define PLAYERTOWN_H

#include <memory>

#include "../../IObject.h"
#include "../../Graphics/Buildings/Town.h"
#include "../TownBuildings.h"

struct BuildInTown
{
  enum TypeBuild{
    Unit,
    Building
  };

  TypeBuild type_build;
  TownBuildings building;
  Units unit;

  BuildInTown(Units type_unit)
    :type_build{TypeBuild::Unit}, unit{type_unit}
  {}

  BuildInTown(TownBuildings type_building)
    :type_build{TypeBuild::Building}, building{type_building}
  {}
};

class PlayerTown : public IObject
{
public:
  PlayerTown(class Town* town, Position position_town);

  Position position_town() const;
  class Town* town() const;

  size_t count_town_buildings() const;
  const std::vector<TownBuildings>& get_town_buildings() const;
  void add_town_building(TownBuildings town_building);

  void add_queue_build(Units type_unit);
  void add_queue_build(TownBuildings type_building);
  void set_build(Units type_unit);
  void set_build(TownBuildings type_building);

  const std::vector<BuildInTown>& get_build_queue() const;
  int get_production() const;
  int get_surplus_production() const;
private:  
  std::unique_ptr<class Town> _town;
  Position _pos;
  int production = 10;
  int surplus_production = 0;

  std::vector<TownBuildings> buildings;
  std::vector<BuildInTown> build_queue;
};

#endif // PLAYERTOWN_H
