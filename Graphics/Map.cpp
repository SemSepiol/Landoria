#include "Map.h"
#include <iostream>

CubicCoordinates::CubicCoordinates(int a, int b)
{
  x = a;
  y = static_cast<int>(round(b*sqrt(3)/2)) + a/2;
  z = static_cast<int>(round(b*sqrt(3)/2)) + a/2;
}

CubicCoordinates::CubicCoordinates(int _x, int _y, int _z)
  :x{_x}, y{_y}, z{_z}
{}

Map::Map(IGameForMap* game)
  :IMap{}, game_controller{game}
{

}

void Map::do_cells()
{
  int c_cell_x = game_controller->count_cell_x();
  int c_cell_y = game_controller->count_cell_y();
  for(int i{0}; i < c_cell_y; ++i)
  {
    cells.push_back(std::vector<std::unique_ptr<Cell>>());
    for(int j{0}; j < c_cell_x; ++j)
      cells[size_t(i)].push_back(std::unique_ptr<Cell>{new Cell{this}});
  }
}

void Map::draw(QPoint point)
{
  point -= QPoint{game_controller->width_map()/2, game_controller->height_map()/2};

  for(size_t i{0}; i < cells.size(); ++i)
    for(size_t j{0}; j < cells[i].size(); ++j)
      cells[i][j]->draw(point_of_cell(j, i) + point);
}

QWidget* Map::window() const
{
  return game_controller->window();
}

Calculations* Map::calculations() const
{
  return game_controller->calculations();
}

Cell* Map::cell_by_index(size_t x, size_t y)
{
  return cells[y][x].get();
}

std::pair<Cell*, IContent*> Map::click(QPoint pos)
{
  auto pair = point_to_indexes_cell(pos);
  size_t i = pair.first;
  size_t j = pair.second;
  if (i == size_t(game_controller->count_cell_y()))
    return {nullptr, nullptr};

  pos += QPoint{game_controller->width_map()/2, game_controller->height_map()/2};
  pos -= point_of_cell(j, i);
  return {cells[i][j].get(), cells[i][j]->click(pos)};
}

int Map::sign(int a)
{
  if (!a)
    return 0;
  return (a>0) ? 1:-1;
}

int Map::coord_to_cub_index(int a)
{
  return (a/calculations()->hexagon_height()+sign(a)) / 2;
}

std::pair<size_t, size_t> Map::point_to_indexes_cell(QPoint pos)
{
  pos += QPoint{game_controller->width_map()/2, game_controller->height_map()/2};
  for(size_t i{0}; i < size_t(game_controller->count_cell_x()); ++i)
    for(size_t j{0}; j < size_t(game_controller->count_cell_y()); ++j)
      if(calculations()->point_in_hexagon(pos - point_of_cell(i, j)))
        return {j, i};
  return {game_controller->count_cell_y(), game_controller->count_cell_x()};
}

QPoint Map::point_of_cell(size_t ind_x, size_t ind_y)
{
  Calculations* calc = calculations();

  int y = int(ind_y+1)*calc->hexagon_side() + int(ind_y)*calc->hexagon_side()/2;
  QPoint cell_point{calc->hexagon_height(), y};
  if (ind_y % 2 == 1)
    cell_point += QPoint{calc->hexagon_height(), 0};

  cell_point += QPoint{calc->hexagon_height()*2*int(ind_x), 0};
  return cell_point;
}
