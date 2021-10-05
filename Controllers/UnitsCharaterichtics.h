#ifndef UNITSCHARATERICHTICS_H
#define UNITSCHARATERICHTICS_H

#include <map>
#include "Enums.h"
#include "../IObject.h"

class UnitsCharaterichtics : public IObject
{
  std::map<Units, int> unit_max_health{
    {Units::Citizen, 10},
    {Units::Bowman, 10},
    {Units::Worker, 10},
    {Units::Swordsman, 10}
  };

  std::map<Units, int> unit_max_movement{
    {Units::Citizen, 2},
    {Units::Bowman, 3},
    {Units::Worker, 2},
    {Units::Swordsman, 2}
  };

public:
  int get_unit_max_health(Units type_unit) const
  { return unit_max_health.at(type_unit); }

  int get_unit_max_movement(Units type_unit) const
  { return unit_max_movement.at(type_unit); }
};


#endif // UNITSCHARATERICHTICS_H
