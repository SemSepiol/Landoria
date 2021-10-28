#ifndef FACTORYSTRING_H
#define FACTORYSTRING_H

#include <map>
#include <QString>

#include "../../IObject.h"
#include "../../Controllers/Enums.h"
#include "../../Controllers/TownBuildings.h"

class FactoryString : IObject
{
  std::map<Resources, std::string> res_str{
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

  std::map<TownBuildings, std::string> building_in_town_str{
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

  std::map<MainLandscapes, std::string> main_landscape_str{
    {MainLandscapes::Ocean, "Океан"},
    {MainLandscapes::Coast, "Побережье"},
    {MainLandscapes::Plain, "Равнина"},
    {MainLandscapes::Mountain, "Горы"},
    {MainLandscapes::Tundra, "Тундра"},
    {MainLandscapes::Desert, "Пустыня"},
    {MainLandscapes::Snow, "Снег"},
    {MainLandscapes::Ice, "Лед"}
  };

  std::map<OtherLandscapes, std::string> other_landscape_str{
    {OtherLandscapes::Nothing, ""},
    {OtherLandscapes::Forest, "Лес"},
    {OtherLandscapes::Jungles, "Джунгли"},
    {OtherLandscapes::Hills, "Холмы"},
    {OtherLandscapes::ForestAndHills, "Холмы, Лес"},
    {OtherLandscapes::JunglesAndHills, "Холмы, Джунгли"}
  };

  std::map<Countries, std::string> country_str{
    {Countries::Nothing, ""},
    {Countries::Russia, "Россия"}
  };

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
