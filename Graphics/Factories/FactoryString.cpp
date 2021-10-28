#include "FactoryString.h"

std::string FactoryString::unit_string(Units type_unit) const
{
  switch (type_unit)
  {
  case Units::Worker:
    return "Рабочии";
  case Units::Citizen:
    return "Поселенецы";
  case Units::Bowman:
    return "Лучники";
  case Units::Swordsman:
    return "Мечники";
  default:
    throw std::runtime_error("unit_string(): Haven't strind for this unit");
  }
}

std::string FactoryString::build_string(Buildings type_building) const
{
  switch (type_building)
  {
  case Buildings::Farm:
    return "Ферма";
  case Buildings::Town:
    return "Город";
  case Buildings::FishingBoat:
    return "Рыбацкая лодка";
  case Buildings::Fort:
    return "Форт";
  case Buildings::LumberMill:
    return "Лесопилка";
  case Buildings::Mine:
    return "Рудник";
  case Buildings::OilWell:
    return "Нефтяная скважина";
  case Buildings::Pasture:
    return "Пастбище";
  case Buildings::Quarry:
    return "Карьер";
  case Buildings::TradingPost:
    return "Торговый пост";
  default:
    throw std::runtime_error("build_string(): Haven't strind for this building");
  }
}

std::string FactoryString::building_in_town_string(TownBuildings type_building) const
{
  return building_in_town_str.at(type_building);
}

std::string FactoryString::resource_string(Resources type_res)
{
  return res_str.at(type_res);
}

std::string FactoryString::landscape_string(MainLandscapes landscape)
{
  return main_landscape_str.at(landscape);
}

std::string FactoryString::landscape_string(OtherLandscapes landscape)
{
  return other_landscape_str.at(landscape);
}

std::string FactoryString::country_string(Countries country)
{
  return country_str.at(country);
}
