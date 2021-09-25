#include "Game.h"

Game::Game(QApplication* app, int count_cell_x, int count_cell_y)
  :graphics_controller {new GraphicsController(this)}
{
  _count_cell_x = count_cell_x;
  _count_cell_y = count_cell_y;
  QSize size_screen = app->primaryScreen()->size();
  _width_win =  size_screen.width();
  _height_win = size_screen.height();
}

void Game::start()
{
  graphics_controller->start();
}

int Game::count_cell_x() const
{
  return _count_cell_x;
}

int Game::count_cell_y() const
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
