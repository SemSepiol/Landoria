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

Map::Map(IGraphicsControllerForMap* game)
  :IMap{}, graphics_controller{game}
{

}

void Map::do_cells()
{
  int c_cell_x = graphics_controller->count_cell_x();
  int c_cell_y = graphics_controller->count_cell_y();
  for(int i{0}; i < c_cell_y; ++i)
  {
    cells.push_back(std::vector<std::unique_ptr<Cell>>());
    for(int j{0}; j < c_cell_x; ++j)
      cells[size_t(i)].push_back(std::unique_ptr<Cell>{new Cell{this}});
  }
}

void Map::draw(QPoint point)
{
  Calculations* calc = calculations();
  int height_win_map = graphics_controller->height_win_map();
  int width_win_map = graphics_controller->width_win_map();

  QPoint corner_of_map_win = graphics_controller->win_map_center() -
      QPoint{width_win_map/2, height_win_map/2};

  QPoint corner_of_map = point -
      QPoint{graphics_controller->width_map()/2, graphics_controller->height_map()/2};

  for(size_t i{0}; i < cells.size(); ++i)
    for(size_t j{0}; j < cells[i].size(); ++j)
    {
      QPoint cell_point = point_of_cell(j, i) + corner_of_map;
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

Cell* Map::cell_by_indexes(size_t x, size_t y) const
{
  return cells[y][x].get();
}

std::pair<size_t, size_t> Map::indexes_by_cell(Cell* cell) const
{
  for(size_t j{0}; j < size_t(graphics_controller->count_cell_y()); ++j)
    for(size_t i{0}; i < size_t(graphics_controller->count_cell_x()); ++i)
      if(cells[j][i].get() == cell)
        return {i,j};
  throw std::runtime_error("indexes_by_cell: Hasn't this got this cell");
}

std::vector<std::pair<size_t, size_t>> Map::adjacent_cells(size_t x, size_t y) const
{
  std::vector<std::pair<size_t, size_t>> res;
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
  auto pair = point_to_indexes_cell(pos);
  size_t i = pair.first;
  size_t j = pair.second;
  if (i == size_t(graphics_controller->count_cell_y())){
//    std::cout << "click: " << pos.x() << " " << pos.y() << std::endl;
    return {nullptr, nullptr};
  }
  pos += QPoint{graphics_controller->width_map()/2, graphics_controller->height_map()/2};
  pos -= point_of_cell(j, i);
  return {cells[i][j].get(), cells[i][j]->click(pos)};
}

QPoint Map::point_of_cell_in_win(size_t ind_x, size_t ind_y)
{
  QPoint corner_of_map = graphics_controller->map_center() -
      QPoint{graphics_controller->width_map()/2, graphics_controller->height_map()/2};
  return point_of_cell(ind_x, ind_y) + corner_of_map;
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
  pos += QPoint{graphics_controller->width_map()/2, graphics_controller->height_map()/2};
  for(size_t i{0}; i < size_t(graphics_controller->count_cell_x()); ++i)
    for(size_t j{0}; j < size_t(graphics_controller->count_cell_y()); ++j){
      if(calculations()->point_in_hexagon(pos - point_of_cell(i, j)))
        return {j, i};
    }
  return {graphics_controller->count_cell_y(), graphics_controller->count_cell_x()};
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
