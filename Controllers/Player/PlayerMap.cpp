#include "PlayerMap.h"

PlayerMap::PlayerMap(Position count_cell)
{
  for(size_t i{0}; i < count_cell.x; ++i)
  {
    map.push_back(std::vector<ICell::ShowCell>{});
    for(size_t j{0}; j < count_cell.y; ++j)
      map[i].push_back(ICell::FogOfWar);
  }
}

ICell::ShowCell PlayerMap::get_show_cell(Position pos_cell) const
{
  //return ICell::Show;
  return map[pos_cell.x][pos_cell.y];
}

void PlayerMap::set_show_cell(Position pos_cell)
{
  map[pos_cell.x][pos_cell.y] = ICell::Show;
}

void PlayerMap::set_notvisible_cell(Position pos_cell)
{
  map[pos_cell.x][pos_cell.y] = ICell::NotVisible;
}
