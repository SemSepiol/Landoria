#ifndef TOWNBUILDNEEDS_H
#define TOWNBUILDNEEDS_H

#include <vector>

#include "Enums.h"
#include "TownBuildings.h"
#include "../IObject.h"


class TownBuildNeeds : public IObject
{
public:
  double get_build_need_production(TownBuildings type_building, int level) const;
  double get_build_need_production(Units type_unit) const;

  std::vector<std::pair<Resources, int>> get_build_need_res(TownBuildings type_building, int level) const;
  std::vector<std::pair<Resources, int>> get_build_need_res(Units type_unit) const;
};

#endif // TOWNBUILDNEEDS_H
