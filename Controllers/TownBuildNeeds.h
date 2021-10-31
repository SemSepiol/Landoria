#ifndef TOWNBUILDNEEDS_H
#define TOWNBUILDNEEDS_H

#include <vector>

#include "../IObject.h"
#include "TownBuildings.h"
#include "Enums.h"

class TownBuildNeeds : public IObject
{
public:
  int get_build_need_production(TownBuildings type_building, int level) const;
  int get_build_need_production(Units type_unit) const;

  std::vector<std::pair<Resources, int>> get_build_need_res(TownBuildings type_building, int level) const;
  std::vector<std::pair<Resources, int>> get_build_need_res(Units type_unit) const;
};

#endif // TOWNBUILDNEEDS_H
