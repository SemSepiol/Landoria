#include "FindUnitVision.h"
#include <iostream>


std::vector<Position> FindUnitVision::unit_vision(class Unit* unit, Position pos_unit, IMapForFind* map) const
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
