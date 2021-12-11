#include "PlayerScience.h"
#include <iostream>

PlayerScience::PlayerScience(Mod _mod)
  :mod{_mod}
{
  //  building.push_back(TownBuildings::Walls);
  //  building.push_back(TownBuildings::Aqueduct);
  //  building.push_back(TownBuildings::Market);
  //  building.push_back(TownBuildings::PublicSchool);
  //  building.push_back(TownBuildings::University);
  //  building.push_back(TownBuildings::Bank);
  //  building.push_back(TownBuildings::MedicalLab);
  //  building.push_back(TownBuildings::ResearchLab);
  //  building.push_back(TownBuildings::Factory);
  //  building.push_back(TownBuildings::Monument);
  //  building.push_back(TownBuildings::Shrine);
  //  building.push_back(TownBuildings::Windmill);
  //  building.push_back(TownBuildings::Museum);
  //  building.push_back(TownBuildings::Hospital);
  //  building.push_back(TownBuildings::Stadium);
  //  building.push_back(TownBuildings::Workshop);
  //  building.push_back(TownBuildings::Library);
  //  building.push_back(TownBuildings::OperaHouse);
  //  building.push_back(TownBuildings::StockExchange);
  //  building.push_back(TownBuildings::Zoo);

  //  best_units.push_back(Units::Citizen);
  //  best_units.push_back(Units::Worker);
  //  best_units.push_back(Units::Bowman);
  //  best_units.push_back(Units::Swordsman);
}

size_t PlayerScience::count_open_buildings() const
{
  return get_open_buildings().size();
}

std::vector<Buildings> PlayerScience::get_open_buildings() const
{
  std::vector<Buildings> res;
  auto science = Science();
  for(auto knowledge : open_knowledges)
    for(auto buildings : science.get_knowledge(knowledge).buildings)
      res.push_back(buildings);
  return res;
}

bool PlayerScience::is_open_building(Buildings building) const
{
  auto buildings = get_open_buildings();
  return std::find(buildings.begin(), buildings.end(), building) != buildings.end();
}

size_t PlayerScience::count_open_resources() const
{
  return get_open_resources().size();
}
std::vector<Resources> PlayerScience::get_open_resources() const
{
  if(mod == Mod::Play)
  {
    std::vector<Resources> res;
    auto science = Science();
    for(auto knowledge : open_knowledges)
      for(auto resource : science.get_knowledge(knowledge).resources)
        res.push_back(resource);
    return res;
  }


  //для разработки
  return {Resources::Fish,
        Resources::Oil,
        Resources::Aluminum,
        Resources::Coal,
        Resources::Horses,
        Resources::Gold,
        Resources::Iron,
        Resources::Silver,
        Resources::Stone,
        Resources::Uranium,};
}

bool PlayerScience::is_open_resource(Resources resource) const
{
  auto resources = get_open_resources();
  return std::find(resources.begin(), resources.end(), resource) != resources.end();
}

size_t PlayerScience::count_open_town_buildings() const
{
  return get_open_town_buildings().size();
}

std::vector<TownBuildings> PlayerScience::get_open_town_buildings() const
{
  std::vector<TownBuildings> res;
  auto science = Science();
  for(auto knowledge : open_knowledges)
    for(auto building : science.get_knowledge(knowledge).town_buildings)
      if(building.level == 1)
        res.push_back(building.town_building);
  return res;
}

size_t PlayerScience::count_open_units() const
{
  return get_open_unit().size();
}

std::vector<Units> PlayerScience::get_open_unit() const
{
  std::vector<Units> res;
  auto science = Science();
  for(auto knowledge : open_knowledges)
    for(auto unit : science.get_knowledge(knowledge).units)
      res.push_back(unit);
  return res;
}

size_t PlayerScience::count_best_open_units() const
{
  return get_best_open_units().size();
}

std::vector<Units> PlayerScience::get_best_open_units() const
{
  return get_open_unit();
}

int PlayerScience::max_level_building(TownBuildings town_building) const
{
  int level = 0;
  auto science = Science();
  for(auto knowledge : open_knowledges)
    for(auto building : science.get_knowledge(knowledge).town_buildings)
      if(building.town_building == town_building)
        if(building.level > level)
          level = building.level;
  return level;
}

bool PlayerScience::is_knowledge_open(Knowledges knowledge) const
{
  return std::find(open_knowledges.begin(), open_knowledges.end(), knowledge)
      != open_knowledges.end();
}

void PlayerScience::set_study_knowledge(Knowledges name_knowledge)
{
  queue_science.clear();
  auto science = Science();
  std::stack<std::pair<Knowledge, size_t>> stack;
  stack.push({science.get_knowledge(name_knowledge), 0});
  while (!stack.empty())
  {
    auto& [knowledge, i] = stack.top();
        auto& need_knowledges = knowledge.necessary_knowledges;
        if(i == need_knowledges.size())
    {
      if(std::find(queue_science.begin(), queue_science.end(), knowledge.name_knowledge) == queue_science.end())
        queue_science.push_back(knowledge.name_knowledge);
      stack.pop();
      continue;
    }

    bool need_push = false;
    std::pair<Knowledge, size_t> push_pair{{name_knowledge},0};
    for(;i < need_knowledges.size(); ++i)
      if(!is_knowledge_open(need_knowledges[i]))
      {
        push_pair = {science.get_knowledge(need_knowledges[i]), 0};
        need_push = true;
        ++i;
        break;
      }
    stack.top().second = i;
    if(need_push)
      stack.push(push_pair);
  }
  std::sort(queue_science.begin(), queue_science.end(),
            [&science](const Knowledges& k1, const Knowledges& k2)
  { return science.get_knowledge(k1).position_knowledge <
        science.get_knowledge(k2).position_knowledge; });

  //  std::cout << "=====" << std::endl;
  //  for(size_t i{0}; i < queue_science.size(); ++i)
  //  {
  //    auto pos = science.get_knowledge(queue_science[i]).position_knowledge;
  //    std::cout << pos.num_x << " " << pos.num_y << std::endl;
  //  }
  //  std::cout << std::endl;
}

const std::vector<Knowledges>& PlayerScience::get_queue_science() const
{
  return queue_science;
}

void PlayerScience::study(double science_glasses)
{
  Knowledges name_knowledge = queue_science[0];
  double need_science_glasses = get_knowledge_science_glasses(name_knowledge);
  if(need_science_glasses > science_glasses + remains_science_glasses)
    knowledge_science_glasses[name_knowledge] = need_science_glasses - science_glasses - remains_science_glasses;
  else
  {
    remains_science_glasses = science_glasses + remains_science_glasses - need_science_glasses;
    knowledge_science_glasses[name_knowledge] = 0;
    open_knowledge(name_knowledge);
    queue_science.erase(queue_science.begin());
  }
}

double PlayerScience::get_knowledge_science_glasses(Knowledges name_knowledge)
{
  if(knowledge_science_glasses.find(name_knowledge) == knowledge_science_glasses.end())
  {
    int science_glasses = Science().get_knowledge(name_knowledge).need_science_glasses;
    knowledge_science_glasses[name_knowledge] = science_glasses;
  }

  return knowledge_science_glasses[name_knowledge];
}

void PlayerScience::open_knowledge(Knowledges name_knowledge)
{
  open_knowledges.push_back(name_knowledge);
}


