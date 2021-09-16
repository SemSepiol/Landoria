#include "Game.h"
#include <iostream>

Game::Game()
  :game_window{new GameWindow(this)}, map{new Map(this)}, calc{new Calculations{}}
{
  num_cell_x = 20;
  num_cell_y = 20;
  calc->set_side(100);

  _height_win = 1000;
  _width_win = 1000;

  do_size_map();
  map_center = center_window();
  map->do_cells();
  do_contents();
}

void Game::start()
{
  game_window->show();
}

QWidget* Game::window() const
{
  return game_window.get();
}

Calculations* Game::calculations() const
{
  return calc.get();
}

int Game::count_cell_x() const
{
  return num_cell_x;
}

int Game::count_cell_y() const
{
  return num_cell_y;
}

int Game::width_win() const
{
  return _width_win;
}

int Game::height_win() const
{
  return _height_win;
}

int Game::width_map() const
{
  return _width_map;
}

int Game::height_map() const
{
  return _height_map;
}

void Game::draw_map()
{
  map->draw(map_center);
}

void Game::move_map(QPoint move_point)
{
  QPoint new_map_center = map_center + move_point;
  if (abs(new_map_center.y() - center_window().y()) + _height_win/2 > _height_map/2)
    move_point.setY(0);
  if (abs(new_map_center.x() - center_window().x()) + _width_win/2 > _width_map/2)
    move_point.setX(0);
  map_center += move_point;
  game_window->update();
}

void Game::resize_map(double coefficient)
{
  int old_side = calc->hexagon_side();
  calc->set_side(calc->my_round(coefficient * calc->hexagon_side()));
  do_size_map();
  if((_height_map < _height_win) ||( _width_map < _width_win))
  {
    calc->set_side(old_side);
    do_size_map();
  }
  else
  {
    if (abs(map_center.x() - center_window().x()) + _width_win/2 > _width_map/2)
    {
      QPoint move = QPoint{abs(map_center.x() - center_window().x()) + _width_win/2 - _width_map/2,0};
      if (map_center.x() - center_window().x() < 0)
        map_center += move;
      else
        map_center -= move;
    }

    if (abs(map_center.x() - center_window().x()) + _width_win/2 > _width_map/2)
    {
      QPoint move = QPoint{abs(map_center.x() - center_window().x()) + _width_win/2 - _width_map/2,0};
      if (map_center.x() - center_window().x() < 0)
        map_center += move;
      else
        map_center -= move;
    }

    if (abs(map_center.y() - center_window().y()) + _height_win/2 > _height_map/2)
    {
      QPoint move = QPoint{0, abs(map_center.y() - center_window().y()) + _height_win/2 - _height_map/2};
      if (map_center.y() - center_window().y() < 0)
        map_center += move;
      else
        map_center -= move;
    }
  }

  game_window->update();
}

void Game::resize_win(const QSize& new_size)
{
//  resize_map(std::max(new_size.width()*1. / _width_win, new_size.height()*1. / _height_win));

  _width_win = new_size.width();
  _height_win = new_size.height();
  game_window->update();
}

QPoint Game::center_window() const
{
  return {_width_win/2, _height_win/2};
}

void Game::do_size_map()
{
  _height_map = calc->hexagon_side()*num_cell_y + calc->hexagon_side()*(num_cell_y+1)/2;
  _width_map = calc->hexagon_height()*(num_cell_x*2+1);
}

void Game::do_contents()
{
  for(int i{0}; i < num_cell_x; ++i)
    for(int j{0}; j < num_cell_y; ++j)
    {
      ControlContents controlcontents{map->cell_by_index(i,j)};
      controlcontents.add_unit(Units::Worker);
      controlcontents.add_unit(Units::Worker);
      controlcontents.add_unit(Units::Worker);
      controlcontents.add_unit(Units::Worker);
    }
//  ControlContents controlcontents{map->cell_by_index(num_cell_x/2, num_cell_y/2)};
//  controlcontents.add_unit(Units::Worker);
//  controlcontents.add_unit(Units::Worker);
//  controlcontents.add_unit(Units::Worker);
//  controlcontents.add_unit(Units::Worker);
}


