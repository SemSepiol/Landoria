#include "Game.h"

Game::Game(int count_cell_x, int count_cell_y)
  :graphics_controller {new GraphicsController(this, count_cell_x, count_cell_y)}
{

}

void Game::start()
{
  graphics_controller->start();
}
