#ifndef GAME_H
#define GAME_H

#include <memory>

#include "IGame.h"
#include "../Graphics/GraphicsController/GraphicsController.h"

class Game : public IGame
{
public:
  Game(int count_cell_x, int count_cell_y);
  void start();
private:
  std::unique_ptr<GraphicsController> graphics_controller;
};

#endif // GAME_H
