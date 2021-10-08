#include "Game.h"
#include <iostream>

Game::Game(QApplication* app, size_t count_cell_x, size_t count_cell_y, size_t count_players)
  :_graphics_controller {new GraphicsController(this)}
{
  _count_cell_x = count_cell_x;
  _count_cell_y = count_cell_y;
  QSize size_screen = app->primaryScreen()->size();
  _width_win =  size_screen.width();
  _height_win = size_screen.height();

  _graphics_controller->create_elements();

  if (count_players < 1)
    throw std::runtime_error("There can't be less than 1 players");
  do_players(count_players);

  _current_player = players[0].get();
}

void Game::start()
{
  _graphics_controller->start();
}

size_t Game::count_cell_x() const
{
  return _count_cell_x;
}

size_t Game::count_cell_y() const
{
  return _count_cell_y;
}

int Game::width_win() const
{
  return _width_win;
}

int Game::height_win() const
{
  return _height_win;
}

IPlayer* Game::current_player() const
{
  return _current_player;
}

IPlayerGraphicsController* Game::graphics_controller() const
{
  return _graphics_controller.get();
}

void Game::do_players(size_t count_players)
{
  for(size_t i{0}; i < count_players; ++i)
  {
    players.push_back(std::unique_ptr<Player>{new Player(this)});
    players[i]->set_initial_units({_count_cell_x/2, _count_cell_y/2});
  }
}
