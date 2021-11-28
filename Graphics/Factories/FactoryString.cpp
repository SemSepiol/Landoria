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
  return building_in_town_str.at(type_building);
}

std::string FactoryString::resource_string(Resources type_res)
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

  return res_str.at(type_res);
}

std::string FactoryString::landscape_string(MainLandscapes landscape)
{
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

  return main_landscape_str.at(landscape);
}

std::string FactoryString::landscape_string(OtherLandscapes landscape)
{
  std::map<OtherLandscapes, std::string> other_landscape_str{
    {OtherLandscapes::Nothing, ""},
    {OtherLandscapes::Forest, "Лес"},
    {OtherLandscapes::Jungles, "Джунгли"},
    {OtherLandscapes::Hills, "Холмы"},
    {OtherLandscapes::ForestAndHills, "Холмы, Лес"},
    {OtherLandscapes::JunglesAndHills, "Холмы, Джунгли"}
  };

  return other_landscape_str.at(landscape);
}

std::string FactoryString::country_string(Countries country)
{
  std::map<Countries, std::string> country_str{
    {Countries::Nothing, ""},
    {Countries::Russia, "Россия"},
    {Countries::America, "Америка"}
  };

  return country_str.at(country);
}

std::string FactoryString::knowledge_string(Knowledges name_knowledge)
{
  switch (name_knowledge)
  {
  case Knowledges::Agriculture:
    return "Земледелие";
  case Knowledges::StoneProcessing:
    return "Обработка Камня";
  case Knowledges::Language:
    return "Язык";
  case Knowledges::WoodProcessing:
    return "Обработка дерева";
  case Knowledges::Writing:
    return "Письменность";
  case Knowledges::AnimalHusbandry:
    return "Животноводство";
  case Knowledges::Wheel:
    return "Колесо";
  case Knowledges::OreMining:
    return "Добыча руды";
  case Knowledges::Archery:
    return "Стрельба из лука";
  case Knowledges::Theology:
    return "Богословие";
  case Knowledges::Navigation:
    return "Мореходство";
  case Knowledges::HorseRiding:
    return "Верховая езда";
  case Knowledges::Winemaking:
    return "Виноделие";
  case Knowledges::BronzeProcessing:
    return "Обработка бронзы";
  case Knowledges::Money:
    return "Деньги";
  case Knowledges::Philosophy:
    return "Философия";
  case Knowledges::Optics:
    return "Оптика";
  case Knowledges::IronProcessing:
    return "Обработка Железа";
  case Knowledges::PreciousOres:
    return "Драгоценные руды";
  case Knowledges::DramaAndPoetry:
    return "Драма и поэзия";
  case Knowledges::Mathematics:
    return "Математика";
  case Knowledges::MetalStructures:
    return "Металлоконструкции";
  case Knowledges::Engineering:
    return "Инженерное дело";
  case Knowledges::Guilds:
    return "Гильдии";
  case Knowledges::Education:
    return "Образование";
  case Knowledges::Compass:
    return "Компас";
  case Knowledges::Knighthood:
    return "Рыцарство";
  case Knowledges::Steelmaking:
    return "Сталеварение";
  case Knowledges::Machinery:
    return "Машиностроение";
  case Knowledges::Trading:
    return "Торговля";
  case Knowledges::Medicine:
    return "Медицина";
  default:
    return "";
  }
}

