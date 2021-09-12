#include "Map.h"
#include <iostream>

Map::Map(IGame* game)
  :IMap{}, game_controller{game}
{

}

void Map::do_cells()
{
  int c_cell_x = game_controller->count_cell_x();
  int c_cell_y = game_controller->count_cell_y();
//  std::cout << "cell_x " << c_cell_x << std::endl;
//  std::cout << "cell_y " << c_cell_y << std::endl;
//  std::cout << cells.size() << std::endl;
  for(int i{0}; i < c_cell_y; ++i)
  {
    std::cout << cells.size() << std::endl;
    cells.push_back(std::vector<std::unique_ptr<Cell>>());
    for(int j{0}; j < c_cell_x; ++j)
      cells[i].push_back(std::unique_ptr<Cell>{new Cell{this}});
  }
}

void Map::draw(QPoint point)
{
//  std::cout << "m " << point.x() << " " << point.y() << std::endl;
  Calculations* calc = game_controller->calculations();

  QPoint cell_point_start = point - QPoint{game_controller->width_map()/2, game_controller->height_map()/2};
  QPoint cell_point = cell_point_start;
  for(size_t i{0}; i < cells.size(); ++i)
  {
    cell_point = cell_point_start;
    int y = int(i+1)*calc->hexagon_side() + int(i)*calc->hexagon_side()/2;
    if (i % 2 == 0)
      cell_point += QPoint{calc->hexagon_height(), y};
    else
      cell_point += QPoint{calc->hexagon_height()*2, y};

    for(size_t j{0}; j < cells[i].size(); ++j)
    {
      cells[i][j]->draw(cell_point);
      cell_point += QPoint{calc->hexagon_height()*2, 0};
    }
  }
}

QWidget* Map::window() const
{
  return game_controller->window();
}

Calculations* Map::calculations() const
{
  return game_controller->calculations();
}
