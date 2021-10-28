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
  _graphics_controller->get_iplayer_gc()->update_res_inform(_current_player);
  do_start_inform();
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
  if(!_current_player->is_finish())
  {
    _current_player->start_move();

    return;
  }
  _current_player->end_move();
  size_t num_player = num_curr_player();
  if(++num_player == players.size())
    num_player = 0;
  _current_player = players[num_player].get();
  do_start_inform();
  _graphics_controller->window()->update();
}

IPlayer* Game::current_player() const
{
  return _current_player;
}

IGameForWidget* Game::igame_for_widget()
{
  return this;
}

IPlayerGraphicsController* Game::graphics_controller() const
{
  return _graphics_controller->get_iplayer_gc();
}

void Game::start_move()
{
  std::cout << "new move" << std::endl;
  _graphics_controller->del_start_inform();
  _current_player->start_move();
}

QWidget* Game::window() const
{
  return _graphics_controller->window();
}

void Game::do_players(size_t count_players)
{
  for(size_t i{0}; i < count_players; ++i)
  {
    players.push_back(std::unique_ptr<Player>{new Player(this, Countries::Russia)});
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

void Game::do_start_inform()
{
  _graphics_controller->do_start_inform("Все хорошо.\n Следующий ход.\n");
}
