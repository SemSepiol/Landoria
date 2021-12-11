#ifndef PLAYERTOWN_H
#define PLAYERTOWN_H

#include <memory>

#include "BuildInTown.h"
#include "ITownPlayer.h"
#include "../../Graphics/Buildings/Town.h"
#include "../../IObject.h"
#include "../TownBuildings.h"
#include "../TownBuildNeeds.h"

struct TownResource
{
  double production_per_turn = 0;
  double coef_production = 1;
  double get_production() const
  { return coef_production * production_per_turn; }

  double gold_per_turn = 0;
  double coef_gold = 1;
  double get_gold() const
  { return coef_gold * gold_per_turn; }

  double science_per_turn = 0;
  double coef_science = 1;
  double get_science() const
  { return coef_science * science_per_turn; }
};


class PlayerTown : public IObject
{
  const size_t _max_build_in_queue = 6;

public:
  PlayerTown(class Town* town, ITownPlayer* player, Position position_town, Mod mod);

  Position position_town() const;
  class Town* town() const;
  void move_build();
  void new_move();

  size_t count_town_buildings() const;
  std::vector<TownBuildings> get_building_already_build() const;
  std::vector<TownBuildings> get_queue_buildings() const;
  std::vector<TownBuildings> get_open_build_buildings() const;
  size_t get_count_can_build() const;
  void add_town_building(TownBuildings town_building);

  void add_queue_build(Units type_unit);
  void add_queue_build(TownBuildings type_building);
  void set_build(Units type_unit);
  void set_build(TownBuildings type_building);
  void del_build(size_t i);
  void move_up_build(size_t i);
  void move_down_build(size_t i);
  size_t max_build_in_queue();

  double get_build_need_production(TownBuildings type_building);
  double get_build_need_production(Units type_unit);

  int get_level_build(TownBuildings type_building);

  const std::vector<BuildInTown*>& get_build_queue() const;
  double get_production() const;
  double get_remains_production() const;

  double get_gold_per_turn() const;
  double get_science_per_turn() const;

  Countries get_country() const;
private:  
  void del_build(BuildInTown* build);

  class Town* _town;
  ITownPlayer* player;
  Position _pos;

  TownResource town_resource{};
  double remains_production = 0;
  bool build_in_this_move = false;

  std::vector<std::unique_ptr<BuildInTown>> build_in_town;
  std::vector<BuildInTown*> build_queue;
  Mod mod;
};

#endif // PLAYERTOWN_H
