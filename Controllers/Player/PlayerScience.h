#ifndef PLAYERSCIENCE_H
#define PLAYERSCIENCE_H

#include <algorithm>
#include <map>
#include <stack>
#include <vector>

#include "../Enums.h"
#include "../Science.h"
#include "../TownBuildings.h"
#include "../../IObject.h"


class PlayerScience : public IObject
{
public:
  PlayerScience();
  size_t count_open_buildings() const;
  std::vector<Buildings> get_open_buildings() const;
  bool is_open_buildings(Buildings building) const;

  size_t count_open_resources() const;
  std::vector<Resources> get_open_resources() const;

  size_t count_open_town_buildings() const;
  std::vector<TownBuildings> get_open_town_buildings() const;

  size_t count_open_units() const;
  std::vector<Units> get_open_unit() const;

  size_t count_best_open_units() const;
  std::vector<Units> get_best_open_units() const;

  int max_level_building(TownBuildings town_building) const;

  bool is_knowledge_open(Knowledges knowledge) const;
  void set_study_knowledge(Knowledges knowledge);
  const std::vector<Knowledges>& get_queue_science() const;

  void study(double science_glasses);
  double get_knowledge_science_glasses(Knowledges knowledge);
private:
  void open_knowledge(Knowledges knowledge);
//  IMenuTownPlayer* player;

  std::vector<Knowledges> queue_science;

  std::vector<Knowledges> open_knowledges{};

  std::map<Knowledges, double> knowledge_science_glasses;
  double remains_science_glasses = 0;
};

#endif // PLAYERSCIENCE_H
