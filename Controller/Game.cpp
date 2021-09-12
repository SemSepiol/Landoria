#include "Game.h"
#include <iostream>

Game::Game()
  :game_window{new GameWindow(this)}, map{new Map(this)}, calc{new Calculations{}}
{
  num_cell_x = 10;
  num_cell_y = 10;
  calc->set_side(50);
  _height_win = calc->hexagon_side()*num_cell_y + calc->hexagon_side()*(num_cell_y+1)/2;
  _width_win = calc->hexagon_height()*(num_cell_x*2+1);

  map->do_cells();
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
  return _width_win;
}

int Game::height_map() const
{
  return _height_win;
}

void Game::draw_map()
{
  map->draw(center_window());
}

QPoint Game::center_window() const
{
  return {_width_win/2, _height_win/2};
}



