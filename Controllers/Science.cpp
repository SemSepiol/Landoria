#include "Science.h"

std::vector<Knowledges> Science::get_all_name_knowledges() const
{
  return std::vector<Knowledges>{
    Knowledges::Agriculture,
        Knowledges::StoneProcessing,
        Knowledges::Language,
        Knowledges::WoodProcessing,
        Knowledges::Writing,
        Knowledges::AnimalHusbandry,
        Knowledges::Wheel,
        Knowledges::OreMining,
        Knowledges::Archery,
        Knowledges::Theology,
        Knowledges::Navigation,
        Knowledges::HorseRiding,
        Knowledges::Winemaking,
        Knowledges::BronzeProcessing,
        Knowledges::Money,
        Knowledges::Philosophy,
        Knowledges::Optics,
        Knowledges::IronProcessing,
        Knowledges::PreciousOres,
        Knowledges::DramaAndPoetry,
        Knowledges::Mathematics,
        Knowledges::MetalStructures,
        Knowledges::Engineering,
        Knowledges::Guilds,
        Knowledges::Education,
        Knowledges::Compass,
        Knowledges::Knighthood,
        Knowledges::Steelmaking,
        Knowledges::Machinery,
        Knowledges::Trading,
        Knowledges::Medicine
  };
}

Knowledge Science::get_knowledge(Knowledges name_knowledge) const
{
  Knowledge knowledge{name_knowledge};
  if(name_knowledge == Knowledges::Agriculture)
  {
    knowledge.position_knowledge = {0,1};
    knowledge.buildings.push_back(Buildings::Farm);
    knowledge.units.push_back(Units::Worker);
    knowledge.units.push_back(Units::Citizen);
  }
  else if(name_knowledge == Knowledges::StoneProcessing)
  {
    knowledge.position_knowledge = {0,2};
    //    knowledge.units.push_back(Units::) Воины
    knowledge.town_buildings.push_back({TownBuildings::Walls, 1});
    knowledge.resources.push_back(Resources::Stone);
    knowledge.buildings.push_back(Buildings::Quarry);
  }
  else if(name_knowledge == Knowledges::Language)
  {
    knowledge.position_knowledge = {0,4};
    knowledge.town_buildings.push_back({TownBuildings::Monument, 1});
  }
  else if(name_knowledge == Knowledges::WoodProcessing)
  {
    knowledge.position_knowledge = {1,2};
    knowledge.necessary_knowledges.push_back(Knowledges::StoneProcessing);
    knowledge.buildings.push_back(Buildings::LumberMill);
  }
  else if(name_knowledge == Knowledges::Writing)
  {
    knowledge.position_knowledge = {1,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Language);
    knowledge.town_buildings.push_back({TownBuildings::PublicSchool, 1});
  }
  else if(name_knowledge == Knowledges::AnimalHusbandry)
  {
    knowledge.position_knowledge = {2,0};
    knowledge.necessary_knowledges.push_back(Knowledges::Agriculture);
    knowledge.resources.push_back(Resources::Horses);
    knowledge.buildings.push_back(Buildings::Pasture);
  }
  else if(name_knowledge == Knowledges::Wheel)
  {
    knowledge.position_knowledge = {2,1};
    knowledge.necessary_knowledges.push_back(Knowledges::Agriculture);
    //    knowledge.units.push_back(Units::) Колесницы
  }
  else if(name_knowledge == Knowledges::OreMining)
  {
    knowledge.position_knowledge = {2,2};
    knowledge.necessary_knowledges.push_back(Knowledges::Agriculture);
    knowledge.necessary_knowledges.push_back(Knowledges::WoodProcessing);
    knowledge.resources.push_back(Resources::Iron);
    knowledge.buildings.push_back(Buildings::Mine);
  }
  else if(name_knowledge == Knowledges::Archery)
  {
    knowledge.position_knowledge = {2,3};
    knowledge.necessary_knowledges.push_back(Knowledges::WoodProcessing);
    knowledge.units.push_back(Units::Bowman);
  }
  else if(name_knowledge == Knowledges::Theology)
  {
    knowledge.position_knowledge = {2,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Writing);
    knowledge.town_buildings.push_back({TownBuildings::Shrine, 1});
    //    knowledge.town_buildings.push_back({TownBuildings::, 1}); Арена
  }
  else if(name_knowledge == Knowledges::Navigation)
  {
    knowledge.position_knowledge = {2,6};
    knowledge.necessary_knowledges.push_back(Knowledges::Writing);
    //    knowledge.units.push_back(Units::); тримера
  }
  else if(name_knowledge == Knowledges::HorseRiding)
  {
    knowledge.position_knowledge = {3,0};
    knowledge.necessary_knowledges.push_back(Knowledges::AnimalHusbandry);
    //    knowledge.units.push_back(Units::) Кавалерия
  }
  else if(name_knowledge == Knowledges::Winemaking)
  {
    knowledge.position_knowledge = {3,1};
    knowledge.necessary_knowledges.push_back(Knowledges::Wheel);
    //    knowledge.town_buildings.push_back({TownBuildings::, 1}); Винодельня
    //    knowledge.town_buildings.push_back({TownBuildings::, 1}); Бани
  }
  else if(name_knowledge == Knowledges::BronzeProcessing)
  {
    knowledge.position_knowledge = {3,2};
    knowledge.necessary_knowledges.push_back(Knowledges::OreMining);
    //    knowledge.units.push_back(Units::); Копейщики
  }
  else if(name_knowledge == Knowledges::Money)
  {
    knowledge.position_knowledge = {3,5};
    knowledge.necessary_knowledges.push_back(Knowledges::Theology);
    knowledge.town_buildings.push_back({TownBuildings::Market, 1});
  }
  else if(name_knowledge == Knowledges::Philosophy)
  {
    knowledge.position_knowledge = {3,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Theology);
    knowledge.town_buildings.push_back({TownBuildings::Library, 1});
    //    knowledge.town_buildings.push_back({TownBuildings::, 1}); Храм
  }
  else if(name_knowledge == Knowledges::Optics)
  {
    knowledge.position_knowledge = {3,6};
    knowledge.necessary_knowledges.push_back(Knowledges::Navigation);
    //    knowledge.town_buildings.push_back({TownBuildings::, 1}); Маяк
  }
  else if(name_knowledge == Knowledges::IronProcessing)
  {
    knowledge.position_knowledge = {4,2};
    knowledge.necessary_knowledges.push_back(Knowledges::Winemaking);
    knowledge.necessary_knowledges.push_back(Knowledges::BronzeProcessing);
    knowledge.necessary_knowledges.push_back(Knowledges::Archery);
    knowledge.units.push_back(Units::Swordsman);
    knowledge.town_buildings.push_back({TownBuildings::Workshop, 1});
  }
  else if(name_knowledge == Knowledges::Mathematics)
  {
    knowledge.position_knowledge = {4,5};
    knowledge.necessary_knowledges.push_back(Knowledges::Money);
    knowledge.town_buildings.push_back({TownBuildings::PublicSchool, 2});
    //    knowledge.units.push_back(Units::); Катапульта
  }
  else if(name_knowledge == Knowledges::DramaAndPoetry)
  {
    knowledge.position_knowledge = {4,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Money);
    knowledge.necessary_knowledges.push_back(Knowledges::Philosophy);
//    knowledge.town_buildings.push_back({TownBuildings::, 1}); Амфитеатор
  }
  else if(name_knowledge == Knowledges::Knighthood)
  {
    knowledge.position_knowledge = {5,0};
    knowledge.necessary_knowledges.push_back(Knowledges::HorseRiding);
    knowledge.necessary_knowledges.push_back(Knowledges::IronProcessing);
    //    knowledge.units.push_back(Units::); Рыцари
    knowledge.town_buildings.push_back({TownBuildings::Walls, 1});
  }
  else if(name_knowledge == Knowledges::PreciousOres)
  {
    knowledge.position_knowledge = {5,3};
    knowledge.necessary_knowledges.push_back(Knowledges::IronProcessing);
    knowledge.necessary_knowledges.push_back(Knowledges::DramaAndPoetry);
    knowledge.resources.push_back(Resources::Gold);
    knowledge.resources.push_back(Resources::Silver);
    //    knowledge.town_buildings.push_back({TownBuildings::, 1}); Казна
  }
  else if(name_knowledge == Knowledges::MetalStructures)
  {
    knowledge.position_knowledge = {5,2};
    knowledge.necessary_knowledges.push_back(Knowledges::IronProcessing);
    //    knowledge.units.push_back(Units::); Крутые лучники
  }
  else if(name_knowledge == Knowledges::Guilds)
  {
    knowledge.position_knowledge = {5,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Mathematics);
    knowledge.necessary_knowledges.push_back(Knowledges::DramaAndPoetry);
    knowledge.buildings.push_back(Buildings::TradingPost);
  }
  else if(name_knowledge == Knowledges::Compass)
  {
    knowledge.position_knowledge = {5,6};
    knowledge.necessary_knowledges.push_back(Knowledges::Mathematics);
    knowledge.necessary_knowledges.push_back(Knowledges::Optics);
    //    knowledge.units.push_back(Units::); Галеас
    //    knowledge.town_buildings.push_back({TownBuildings::, 1}); Гавань
  }
  else if(name_knowledge == Knowledges::Engineering)
  {
    knowledge.position_knowledge = {6,3};
    knowledge.necessary_knowledges.push_back(Knowledges::IronProcessing);
    knowledge.necessary_knowledges.push_back(Knowledges::Guilds);
    knowledge.town_buildings.push_back({TownBuildings::Aqueduct, 1});
    knowledge.buildings.push_back(Buildings::Fort);
  }
  else if(name_knowledge == Knowledges::Education)
  {
    knowledge.position_knowledge = {6,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Mathematics);
    knowledge.town_buildings.push_back({TownBuildings::University, 1});
    knowledge.town_buildings.push_back({TownBuildings::Library, 2});
  }
  else if(name_knowledge == Knowledges::Steelmaking)
  {
    knowledge.position_knowledge = {7,2};
    knowledge.necessary_knowledges.push_back(Knowledges::MetalStructures);
    //    knowledge.units.push_back(Units::); Крутые мечники
  }
  else if(name_knowledge == Knowledges::Machinery)
  {
    knowledge.position_knowledge = {7,3};
    knowledge.necessary_knowledges.push_back(Knowledges::MetalStructures);
    knowledge.necessary_knowledges.push_back(Knowledges::Engineering);
    knowledge.town_buildings.push_back({TownBuildings::Workshop, 2});
    //    knowledge.units.push_back(Units::); Требушет
  }
  else if(name_knowledge == Knowledges::Trading)
  {
    knowledge.position_knowledge = {7,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Guilds);
    knowledge.necessary_knowledges.push_back(Knowledges::Education);
    knowledge.town_buildings.push_back({TownBuildings::Market, 2});
    knowledge.town_buildings.push_back({TownBuildings::Bank, 1});
  }
  else if(name_knowledge == Knowledges::Medicine)
  {
    knowledge.position_knowledge = {7,5};
    knowledge.necessary_knowledges.push_back(Knowledges::Education);
    knowledge.town_buildings.push_back({TownBuildings::Hospital, 1});
  }
  else
    throw std::runtime_error("There are no images for this resource");

  return knowledge;
}
