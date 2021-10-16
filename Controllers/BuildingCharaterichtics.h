#ifndef BUILDINGCHARATERICHTICS_H
#define BUILDINGCHARATERICHTICS_H

#include <map>
#include "Enums.h"
#include "../IObject.h"

class BuildingCharaterichtics : public IObject
{
  std::map<Buildings, int> count_phase{
    {Farm, 30},
    {FishingBoat, 30},
    {Fort, 30},
    {LumberMill, 30},
    {Mine, 30},
    {OilWell, 30},
    {Pasture, 30},
    {Quarry, 30},
    {TradingPost, 30}
  };

public:
  int get_building_count_phase(Buildings type_building)
  { return count_phase.at(type_building); }
};

#endif // BUILDINGCHARATERICHTICS_H
