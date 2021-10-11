#include "Map.h"
#include <iostream>

Map::Map(IMapGraphicsController* game)
  :IMap{}, graphics_controller{game}
{

}

void Map::do_cells()
{
  size_t c_cell_x = graphics_controller->count_cell_x();
  size_t c_cell_y = graphics_controller->count_cell_y();
  for(size_t i{0}; i < c_cell_y; ++i)
  {
    cells.push_back(std::vector<std::unique_ptr<Cell>>());
    for(size_t j{0}; j < c_cell_x; ++j)
      cells[i].push_back(std::unique_ptr<Cell>{new Cell{this}});
  }
}

void Map::draw(QPoint point)
{
  Calculations* calc = calculations();
  Size size_win_map = graphics_controller->size_win_map();
  int height_win_map = size_win_map.height;
  int width_win_map = size_win_map.width;
  Size size_map = graphics_controller->size_map();
  int width_map = size_map.width;
  int height_map = size_map.height;


  QPoint corner_of_map_win = graphics_controller->win_map_center() -
      QPoint{width_win_map/2, height_win_map/2};

  QPoint corner_of_map = point -
      QPoint{width_map/2, height_map/2};

  for(size_t i{0}; i < cells.size(); ++i)
    for(size_t j{0}; j < cells[i].size(); ++j)
    {
      QPoint cell_point = point_of_cell({j, i}) + corner_of_map;
      if (cell_point.x() + calc->hexagon_height() < corner_of_map_win.x())
        continue;
      if (cell_point.x() - calc->hexagon_height() > corner_of_map_win.x() + width_win_map)
        continue;
      if (cell_point.y() + calc->hexagon_side() < corner_of_map_win.y())
        continue;
      if (cell_point.y() - calc->hexagon_side() > corner_of_map_win.y() + height_win_map)
        continue;
      cells[i][j]->draw(cell_point);
    }
}

QWidget* Map::window() const
{
  return graphics_controller->window();
}

Calculations* Map::calculations() const
{
  return graphics_controller->calculations();
}

ICell* Map::icell_by_indexes(Position pos) const
{
  return cell_by_indexes(pos);
}

Cell* Map::cell_by_indexes(Position pos) const
{
  return cells[pos.y][pos.x].get();
}

Position Map::indexes_by_cell(Cell* cell) const
{
  for(size_t j{0}; j < size_t(graphics_controller->count_cell_y()); ++j)
    for(size_t i{0}; i < size_t(graphics_controller->count_cell_x()); ++i)
      if(cells[j][i].get() == cell)
        return {i,j};
  throw std::runtime_error("indexes_by_cell: Hasn't this got this cell");
}

std::vector<Position> Map::adjacent_cells(Position pos) const
{
  size_t x = pos.x;
  size_t y = pos.y;
  std::vector<Position> res;
  size_t max_ind_x =  size_t(graphics_controller->count_cell_x() - 1);
  size_t max_ind_y =  size_t(graphics_controller->count_cell_y() - 1);


  if(y < max_ind_y)
    res.push_back({x, y+1});
  if(y > 0)
    res.push_back({x, y-1});

  if(x > 0)
    res.push_back({x-1, y});
  if(x < max_ind_x)
    res.push_back({x+1, y});

  if (y % 2 == 0 && x > 0)
  {
    if(y > 0)
      res.push_back({x-1, y-1});

    if(y < max_ind_y)
      res.push_back({x-1, y+1});
  }
  else if(y % 2 == 1 && x < max_ind_x)
  {
    if(y > 0)
      res.push_back({x+1, y-1});

    if(y < max_ind_y)
        res.push_back({x+1, y+1});
  }

  return res;
}

std::pair<Cell*, IContent*> Map::click(QPoint pos)
{
  Position cell_pos = point_to_indexes_cell(pos);
  size_t i = cell_pos.x;
  size_t j = cell_pos.y;
  if (i == size_t(graphics_controller->count_cell_y()))
    return {nullptr, nullptr};

  Size size_map = graphics_controller->size_map();
  int width_map = size_map.width;
  int height_map = size_map.height;

  pos += QPoint{width_map/2, height_map/2};
  pos -= point_of_cell({j, i});
  return {cells[i][j].get(), cells[i][j]->click(pos)};
}

QPoint Map::point_of_cell_in_win(Position pos)
{
  Size size_map = graphics_controller->size_map();
  int width_map = size_map.width;
  int height_map = size_map.height;

  QPoint corner_of_map = graphics_controller->map_center() -
      QPoint{width_map/2, height_map/2};
  return point_of_cell(pos) + corner_of_map;
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

Position Map::point_to_indexes_cell(QPoint pos)
{
  Size size_map = graphics_controller->size_map();
  int width_map = size_map.width;
  int height_map = size_map.height;

  pos += QPoint{width_map/2, height_map/2};
  for(size_t i{0}; i < size_t(graphics_controller->count_cell_x()); ++i)
    for(size_t j{0}; j < size_t(graphics_controller->count_cell_y()); ++j){
      if(calculations()->point_in_hexagon(pos - point_of_cell({i, j})))
        return {j, i};
    }
  return {graphics_controller->count_cell_y(), graphics_controller->count_cell_x()};
}

QPoint Map::point_of_cell(Position pos)
{
  Calculations* calc = calculations();

  int y = int(pos.y+1)*calc->hexagon_side() + int(pos.y)*calc->hexagon_side()/2;
  QPoint cell_point{calc->hexagon_height(), y};
  if (pos.y % 2 == 1)
    cell_point += QPoint{calc->hexagon_height(), 0};

  cell_point += QPoint{calc->hexagon_height()*2*int(pos.x), 0};
  return cell_point;
}
