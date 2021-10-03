#include "FindUnitWay.h"
#include "iostream"


void OneMove::add_move(Position pos)
{
  minimove.push_back(pos);
  end = pos;
}

OneMove Way::get_move_in_way(size_t num_move) const{
  if(num_move > way.size())
    throw std::runtime_error("get_move_in_way(): The path has fewer moves");
  return way[num_move];
}

size_t Way::get_count_moves_in_way() const
{
  return way.size();
}

void Way::add_move(OneMove move)
{
  way.push_back(move);
}

Way FindUnitWay::get_way(class Unit *unit, Map *map, Position start, Position end)
{
  Position go{start};
  Way way;
  OneMove onemove{start};

  int movement_points = unit->get_movement();
  if (!movement_points)
    movement_points = unit->get_max_movement();
  while(go != end)
  {
    std::vector<std::pair<size_t, size_t>> neighbors =  map->adjacent_cells(go.x, go.y);
    Position min_distance{neighbors[0]};
    for(size_t i{1}; i < neighbors.size(); ++i)
    {
      Position temp{neighbors[i]};
      if(abs(int(temp.y) - int(end.y)) < abs(int(min_distance.y) - int(end.y)))
        min_distance = temp;
      if(abs(int(temp.y) - int(end.y)) == abs(int(min_distance.y) - int(end.y)))
        if(abs(int(temp.x) - int(end.x)) < abs(int(min_distance.x) - int(end.x)))
          min_distance = temp;
    }
    onemove.add_move(min_distance);
    onemove.spent_movement_points++;
    go = min_distance;
    --movement_points;
    if(!movement_points)
    {
      movement_points = unit->get_max_movement();
      way.add_move(onemove);
      onemove = OneMove{min_distance};
    }
  }
  way.add_move(onemove);
  return way;
}

OneMove FindUnitWay::get_first_move(class Unit* unit, Map* map, Position start, Position end)
{
  return get_way(unit, map, start, end).get_move_in_way(0);
}
