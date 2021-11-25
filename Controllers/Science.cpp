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
  }
  else if(name_knowledge == Knowledges::StoneProcessing)
  {
    knowledge.position_knowledge = {0,2};
  }
  else if(name_knowledge == Knowledges::Language)
  {
    knowledge.position_knowledge = {0,4};
  }
  else if(name_knowledge == Knowledges::WoodProcessing)
  {
    knowledge.position_knowledge = {1,2};
    knowledge.necessary_knowledges.push_back(Knowledges::StoneProcessing);
  }
  else if(name_knowledge == Knowledges::Writing)
  {
    knowledge.position_knowledge = {1,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Language);
  }
  else if(name_knowledge == Knowledges::AnimalHusbandry)
  {
    knowledge.position_knowledge = {2,0};
    knowledge.necessary_knowledges.push_back(Knowledges::Agriculture);
  }
  else if(name_knowledge == Knowledges::Wheel)
  {
    knowledge.position_knowledge = {2,1};
    knowledge.necessary_knowledges.push_back(Knowledges::Agriculture);
  }
  else if(name_knowledge == Knowledges::OreMining)
  {
    knowledge.position_knowledge = {2,2};
    knowledge.necessary_knowledges.push_back(Knowledges::Agriculture);
    knowledge.necessary_knowledges.push_back(Knowledges::WoodProcessing);
  }
  else if(name_knowledge == Knowledges::Archery)
  {
    knowledge.position_knowledge = {2,3};
    knowledge.necessary_knowledges.push_back(Knowledges::WoodProcessing);
  }
  else if(name_knowledge == Knowledges::Theology)
  {
    knowledge.position_knowledge = {2,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Writing);
  }
  else if(name_knowledge == Knowledges::Navigation)
  {
    knowledge.position_knowledge = {2,6};
    knowledge.necessary_knowledges.push_back(Knowledges::Writing);
  }
  else if(name_knowledge == Knowledges::HorseRiding)
  {
    knowledge.position_knowledge = {3,0};
    knowledge.necessary_knowledges.push_back(Knowledges::AnimalHusbandry);
  }
  else if(name_knowledge == Knowledges::Winemaking)
  {
    knowledge.position_knowledge = {3,1};
    knowledge.necessary_knowledges.push_back(Knowledges::Wheel);
  }
  else if(name_knowledge == Knowledges::BronzeProcessing)
  {
    knowledge.position_knowledge = {3,2};
    knowledge.necessary_knowledges.push_back(Knowledges::OreMining);
  }
  else if(name_knowledge == Knowledges::Money)
  {
    knowledge.position_knowledge = {3,5};
    knowledge.necessary_knowledges.push_back(Knowledges::Theology);
  }
  else if(name_knowledge == Knowledges::Philosophy)
  {
    knowledge.position_knowledge = {3,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Theology);
  }
  else if(name_knowledge == Knowledges::Optics)
  {
    knowledge.position_knowledge = {3,6};
    knowledge.necessary_knowledges.push_back(Knowledges::Navigation);
  }
  else if(name_knowledge == Knowledges::IronProcessing)
  {
    knowledge.position_knowledge = {4,2};
    knowledge.necessary_knowledges.push_back(Knowledges::Winemaking);
    knowledge.necessary_knowledges.push_back(Knowledges::BronzeProcessing);
  }
  else if(name_knowledge == Knowledges::PreciousOres)
  {
    knowledge.position_knowledge = {4,3};
    knowledge.necessary_knowledges.push_back(Knowledges::Money);
    knowledge.necessary_knowledges.push_back(Knowledges::BronzeProcessing);
  }
  else if(name_knowledge == Knowledges::Mathematics)
  {
    knowledge.position_knowledge = {4,5};
    knowledge.necessary_knowledges.push_back(Knowledges::Money);
  }
  else if(name_knowledge == Knowledges::DramaAndPoetry)
  {
    knowledge.position_knowledge = {4,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Money);
    knowledge.necessary_knowledges.push_back(Knowledges::Philosophy);
  }
  else if(name_knowledge == Knowledges::Knighthood)
  {
    knowledge.position_knowledge = {5,0};
    knowledge.necessary_knowledges.push_back(Knowledges::HorseRiding);
    knowledge.necessary_knowledges.push_back(Knowledges::IronProcessing);
  }
  else if(name_knowledge == Knowledges::MetalStructures)
  {
    knowledge.position_knowledge = {5,2};
    knowledge.necessary_knowledges.push_back(Knowledges::IronProcessing);
  }
  else if(name_knowledge == Knowledges::Guilds)
  {
    knowledge.position_knowledge = {5,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Mathematics);
    knowledge.necessary_knowledges.push_back(Knowledges::DramaAndPoetry);
  }
  else if(name_knowledge == Knowledges::Compass)
  {
    knowledge.position_knowledge = {5,7};
    knowledge.necessary_knowledges.push_back(Knowledges::Mathematics);
    knowledge.necessary_knowledges.push_back(Knowledges::Optics);
  }
  else if(name_knowledge == Knowledges::Engineering)
  {
    knowledge.position_knowledge = {6,3};
    knowledge.necessary_knowledges.push_back(Knowledges::IronProcessing);
    knowledge.necessary_knowledges.push_back(Knowledges::Guilds);
  }
  else if(name_knowledge == Knowledges::Education)
  {
    knowledge.position_knowledge = {6,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Mathematics);
  }
  else if(name_knowledge == Knowledges::Steelmaking)
  {
    knowledge.position_knowledge = {7,2};
    knowledge.necessary_knowledges.push_back(Knowledges::MetalStructures);
  }
  else if(name_knowledge == Knowledges::Machinery)
  {
    knowledge.position_knowledge = {7,3};
    knowledge.necessary_knowledges.push_back(Knowledges::MetalStructures);
    knowledge.necessary_knowledges.push_back(Knowledges::Engineering);
  }
  else if(name_knowledge == Knowledges::Trading)
  {
    knowledge.position_knowledge = {7,4};
    knowledge.necessary_knowledges.push_back(Knowledges::Guilds);
    knowledge.necessary_knowledges.push_back(Knowledges::Education);
  }
  else if(name_knowledge == Knowledges::Medicine)
  {
    knowledge.position_knowledge = {7,5};
    knowledge.necessary_knowledges.push_back(Knowledges::Education);
  }
  else
    throw std::runtime_error("There are no images for this resource");

  return knowledge;
}
