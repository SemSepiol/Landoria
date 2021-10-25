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
  switch (type_building)
  {
  case TownBuildings::Aqueduct:
    return QString("Акведук");
  case TownBuildings::Market:
    return QString("Город");
  case TownBuildings::PublicSchool:
    return QString("Рыбацкая лодка");
  case TownBuildings::University:
    return QString("Форт");
  case TownBuildings::Bank:
    return QString("Лесопилка");
  case TownBuildings::Medical_Lab:
    return QString("Рудник");
  case TownBuildings::ResearchLab:
    return QString("Нефтяная скважина");
  case TownBuildings::Walls:
    return QString("Стены");
  case TownBuildings::Monument:
    return QString("Карьер");
  case TownBuildings::Shrine:
    return QString("Cвятилище");
  case TownBuildings::Windmill:
    return QString("Ветряная мельница");
  case TownBuildings::Hospital:
    return QString("Больница");
  case TownBuildings::Stadium:
    return QString("Стадион");
  case TownBuildings::Workshop:
    return QString("Мастерская");
  case TownBuildings::Library:
    return QString("Библиотека");
  case TownBuildings::OperaHouse:
    return QString("Опера");
  case TownBuildings::StockExchange:
    return QString("Биржа");
  case TownBuildings::Zoo:
    return QString("Зоопарк");
  case TownBuildings::Factory:
    return QString("Фабрика");
  case TownBuildings::Museum:
    return QString("Музей");
  default:
    throw std::runtime_error("build_in_town_string(): Haven't strind for this building");
  }
}

QString FactoryString::resource_string(Resources type_res)
{
  return res_string.at(type_res);
}
