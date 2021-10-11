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
  _current_player->draw_my_map();
  _current_player->start_move();
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

void Game::next_move()
{
  _current_player->end_move();
  size_t num_player = num_curr_player();
  if(++num_player == players.size())
    num_player = 0;
  _current_player = players[num_player].get();
  _current_player->start_move();
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
    players[i]->set_initial_units({10, 10});
  }
}

size_t Game::num_curr_player()
{
  for(size_t i{0}; i < players.size(); ++i)
    if(players[i].get() == _current_player)
      return i;
  throw std::runtime_error("Cann't find current player");
}
