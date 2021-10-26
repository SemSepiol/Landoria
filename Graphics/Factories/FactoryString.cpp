#include "FactoryString.h"

QString FactoryString::unit_string(Units type_unit) const
{
  switch (type_unit)
  {
  case Units::Worker:
    return QString("Рабочии");
  case Units::Citizen:
    return QString("Поселенецы");
  case Units::Bowman:
    return QString("Лучники");
  case Units::Swordsman:
    return QString("Мечники");
  default:
    throw std::runtime_error("unit_string(): Haven't strind for this unit");
  }
}

QString FactoryString::build_string(Buildings type_building) const
{
  switch (type_building)
  {
  case Buildings::Farm:
    return QString("Ферма");
  case Buildings::Town:
    return QString("Город");
  case Buildings::FishingBoat:
    return QString("Рыбацкая лодка");
  case Buildings::Fort:
    return QString("Форт");
  case Buildings::LumberMill:
    return QString("Лесопилка");
  case Buildings::Mine:
    return QString("Рудник");
  case Buildings::OilWell:
    return QString("Нефтяная скважина");
  case Buildings::Pasture:
    return QString("Пастбище");
  case Buildings::Quarry:
    return QString("Карьер");
  case Buildings::TradingPost:
    return QString("Торговый пост");
  default:
    throw std::runtime_error("build_string(): Haven't strind for this building");
  }
}

QString FactoryString::building_in_town_string(TownBuildings type_building) const
{
  return building_in_town_str.at(type_building);
}

QString FactoryString::resource_string(Resources type_res)
{
  return res_str.at(type_res);
}
