#ifndef PLAYERTOWN_H
#define PLAYERTOWN_H

#include <memory>

#include "../../IObject.h"
#include "../../Graphics/Buildings/Town.h"
#include "../TownBuildings.h"
#include "../TownBuildNeeds.h"
#include "ITownPlayer.h"

struct BuildInTown
{
  enum TypeBuild{
    Unit,
    Building
  };

  TypeBuild type_build;
  TownBuildings building;
  Units unit;
  int need_production;

  BuildInTown(Units type_unit)
    :type_build{TypeBuild::Unit}, unit{type_unit}
  {
    need_production = TownBuildNeeds().get_build_need_production(type_unit);
  }

  BuildInTown(TownBuildings type_building)
    :type_build{TypeBuild::Building}, building{type_building}
  {
    need_production = TownBuildNeeds().get_build_need_production(type_building);
  }

  //возвращает остаток
  int build(int town_production);
};

class PlayerTown : public IObject
{
  const size_t _max_build_in_queue = 6;

public:
  PlayerTown(class Town* town, ITownPlayer* player, Position position_town);

  Position position_town() const;
  class Town* town() const;
  void move_build();
  void new_move();

  size_t count_town_buildings() const;
  std::vector<TownBuildings> get_building_already_build() const;
  std::vector<TownBuildings> get_queue_buildings() const;
  void add_town_building(TownBuildings town_building);

  void add_queue_build(Units type_unit);
  void add_queue_build(TownBuildings type_building);
  void set_build(Units type_unit);
  void set_build(TownBuildings type_building);
  void del_build(size_t i);
  void move_up_build(size_t i);
  void move_down_build(size_t i);
  size_t max_build_in_queue();

  int get_build_need_production(TownBuildings type_building);
  int get_build_need_production(Units type_unit);

  const std::vector<BuildInTown*>& get_build_queue() const;
  int get_production() const;
  int get_remains_production() const;
private:  
  void del_build(BuildInTown* build);

  class Town* _town;
  ITownPlayer* player;
  Position _pos;
  int production = 10;
  int remains_production = 0;
  bool build_in_this_move = false;

  std::vector<std::unique_ptr<BuildInTown>> build_in_town;
  std::vector<BuildInTown*> build_queue;
};

#endif // PLAYERTOWN_H
