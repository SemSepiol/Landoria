#ifndef BUILDINGCHARATERICHTICS_H
#define BUILDINGCHARATERICHTICS_H

#include <map>

#include "../../Controllers/Enums.h"
#include "../../IObject.h"


class BuildingCharaterichtics : public IObject
{
  std::map<Buildings, int> count_phase{
    {Buildings::Farm, 30},
    {Buildings::FishingBoat, 30},
    {Buildings::Fort, 30},
    {Buildings::LumberMill, 30},
    {Buildings::Mine, 30},
    {Buildings::OilWell, 30},
    {Buildings::Pasture, 30},
    {Buildings::Quarry, 30},
    {Buildings::TradingPost, 30}
  };

public:
  int get_building_count_phase(Buildings type_building)
  { return count_phase.at(type_building); }
};

#endif // BUILDINGCHARATERICHTICS_H
