#ifndef FACTORYSTRING_H
#define FACTORYSTRING_H

#include <map>
#include <QString>

#include "../Map/TypeMap.h"
#include "../../Controllers/Enums.h"
#include "../../Controllers/Science.h"
#include "../../Controllers/TownBuildings.h"
#include "../../IObject.h"


class FactoryString : IObject
{
public:
  std::string unit_string(Units type_unit) const;
  std::string build_string(Buildings type_building) const;
  std::string building_in_town_string(TownBuildings type_building) const;
  std::string resource_string(Resources type_res) const;
  std::string landscape_string(MainLandscapes landscape) const;
  std::string landscape_string(OtherLandscapes landscape) const;
  std::string country_string(Countries country) const;
  std::string knowledge_string(Knowledges name_knowledge) const;
  std::string typemap_overlay_string(TypeMap::Overlay overlay) const;
  std::string typemap_typecontent_string(TypeMap::TypeContent typecontent) const;
};

#endif // FACTORYSTRING_H
