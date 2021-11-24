#ifndef FACTORYSTRING_H
#define FACTORYSTRING_H

#include <map>
#include <QString>

#include "../../Controllers/Enums.h"
#include "../../Controllers/TownBuildings.h"
#include "../../IObject.h"


class FactoryString : IObject
{
public:
  std::string unit_string(Units type_unit) const;
  std::string build_string(Buildings type_building) const;
  std::string building_in_town_string(TownBuildings type_building) const;
  std::string resource_string(Resources type_res);
  std::string landscape_string(MainLandscapes landscape);
  std::string landscape_string(OtherLandscapes landscape);
  std::string country_string(Countries country);
};

#endif // FACTORYSTRING_H
