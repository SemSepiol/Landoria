#include "Game.h"

Game::Game()
  :game_window{new GameWindow(this)}, map{new Map(this)}
{

}

void Game::start()
{
  game_window->show();
}

QWidget* Game::window()
{
  return game_window.get();
}
