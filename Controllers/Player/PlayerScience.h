#ifndef PLAYERSCIENCE_H
#define PLAYERSCIENCE_H

#include <algorithm>
#include <vector>

#include "../Enums.h"
#include "../Science.h"
#include "../TownBuildings.h"
#include "../../IObject.h"


class PlayerScience : public IObject
{
public:
  PlayerScience();
  size_t count_open_town_buildings() const;
  const std::vector<TownBuildings>& get_open_town_buildings() const;

  size_t count_open_units() const;
  Units get_open_unit(size_t ind) const;

  size_t count_best_open_units() const;
  const std::vector<Units>& get_best_open_units() const;

  int max_level_building(TownBuildings building) const;

  bool is_knowledge_open(Knowledges knowledge) const;
  void set_study_knowledge(Knowledges knowledge);

private:
//  IMenuTownPlayer* player;

  std::vector<TownBuildings> building;
  std::vector<Units> units;
  std::vector<Units> best_units;

  std::vector<Knowledges> queue_science;

  std::vector<Knowledges> open_knowledges{};
};

#endif // PLAYERSCIENCE_H
