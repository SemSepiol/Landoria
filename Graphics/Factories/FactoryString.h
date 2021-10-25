#ifndef FACTORYSTRING_H
#define FACTORYSTRING_H

#include <map>
#include <QString>

#include "../../IObject.h"
#include "../../Controllers/Enums.h"
#include "../../Controllers/TownBuildings.h"

class FactoryString : IObject
{
  std::map<Resources, QString> res_string{
    {Iron, "Железо"},
    {Gold, "Золото"},
    {Stone, "Камень"},
    {Aluminum, "Алюминий"},
    {Horses, "Лошади"},
    {Oil, "Нефть"},
    {Uranium, "Уран"},
    {Coal, "Уголь"},
    {Fish, "Рыба"},
    {Silver, "Серебро"},
  };

public:
  QString unit_string(Units type_unit) const;
  QString build_string(Buildings type_building) const;
  QString building_in_town_string(TownBuildings type_building) const;
  QString resource_string(Resources type_res);
};

#endif // FACTORYSTRING_H
