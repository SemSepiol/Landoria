#include "FindVision.h"
#include <iostream>


std::vector<Position> FindVision::unit_vision(class Unit* unit, Position pos_unit, IMapForFind* map) const
{
  std::vector<Position> res;

  std::queue<std::pair<Position, int>> queue;
  queue.push({pos_unit, unit->get_vision()});
  while(!queue.empty()){
    std::pair<Position, int> pair = queue.front();
    queue.pop();
    if(std::find(res.begin(), res.end(), pair.first) == res.end())
      res.push_back(pair.first);

    if(pair.second != 0)
      for(Position pos : map->adjacent_cells(pair.first))
        queue.push({pos, pair.second-1});
  }
  return res;
}

std::vector<Position> FindVision::town_vision(PlayerTown* town, IMapForFind* map) const
{
  std::vector<Position> res;

  std::queue<std::pair<Position, int>> queue;
  queue.push({town->position_town(), 3});
  while(!queue.empty()){
    std::pair<Position, int> pair = queue.front();
    queue.pop();
    if(std::find(res.begin(), res.end(), pair.first) == res.end())
    {
      Countries country_cell = map->get_cell_country(pair.first);
      bool is_visible = false;

      if(town->get_country() == country_cell)
        is_visible = true;

      for(auto pos : map->adjacent_cells(pair.first))
      {
        country_cell = map->get_cell_country(pos);
        if(town->get_country() == country_cell)
          is_visible = true;
      }
      if(is_visible)
        res.push_back(pair.first);
    }

    if(pair.second != 0)
      for(Position pos : map->adjacent_cells(pair.first))
        queue.push({pos, pair.second-1});
  }
  return res;
}
