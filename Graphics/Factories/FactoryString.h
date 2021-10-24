#ifndef FACTORYSTRING_H
#define FACTORYSTRING_H

#include <QString>

#include "../../IObject.h"
#include "../../Controllers/Enums.h"
#include "../../Controllers/TownBuildings.h"

class FactoryString : IObject
{
public:
  QString unit_string(Units type_unit) const;
  QString build_string(Buildings type_building) const;
  QString building_in_town_string(TownBuildings type_building) const;
};

#endif // FACTORYSTRING_H
