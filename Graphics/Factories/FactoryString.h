#ifndef FACTORYSTRING_H
#define FACTORYSTRING_H

#include <map>
#include <QString>

#include "../../IObject.h"
#include "../../Controllers/Enums.h"
#include "../../Controllers/TownBuildings.h"

class FactoryString : IObject
{
  std::map<Resources, QString> res_str{
    {Resources::Iron, "Железо"},
    {Resources::Gold, "Золото"},
    {Resources::Stone, "Камень"},
    {Resources::Aluminum, "Алюминий"},
    {Resources::Horses, "Лошади"},
    {Resources::Oil, "Нефть"},
    {Resources::Uranium, "Уран"},
    {Resources::Coal, "Уголь"},
    {Resources::Fish, "Рыба"},
    {Resources::Silver, "Серебро"},
  };

  std::map<TownBuildings, QString> building_in_town_str{
    {TownBuildings::Aqueduct, "Акведук"},
    {TownBuildings::Market, "Рынок"},
    {TownBuildings::PublicSchool, "Школа"},
    {TownBuildings::University, "Университет"},
    {TownBuildings::Bank, "Банк"},
    {TownBuildings::MedicalLab, "Медицинская лаборатория"},
    {TownBuildings::ResearchLab, "Лаборатория"},
    {TownBuildings::Walls, "Стены"},
    {TownBuildings::Monument, "Монумент"},
    {TownBuildings::Shrine, "Cвятилище"},
    {TownBuildings::Windmill, "Ветряная мельница"},
    {TownBuildings::Hospital, "Больница"},
    {TownBuildings::Stadium, "Стадион"},
    {TownBuildings::Workshop, "Мастерская"},
    {TownBuildings::Library, "Библиотека"},
    {TownBuildings::OperaHouse, "Опера"},
    {TownBuildings::StockExchange, "Биржа"},
    {TownBuildings::Zoo, "Зоопарк"},
    {TownBuildings::Factory, "Фабрика"},
    {TownBuildings::Museum, "Музей"}
  };

public:
  QString unit_string(Units type_unit) const;
  QString build_string(Buildings type_building) const;
  QString building_in_town_string(TownBuildings type_building) const;
  QString resource_string(Resources type_res);
};

#endif // FACTORYSTRING_H
