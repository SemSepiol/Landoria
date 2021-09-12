#ifndef GAME_H
#define GAME_H

#include <memory>
#include <QWidget>

#include "IGame.h"
#include "../Graphics/GameWindow.h"
#include "../Graphics/Map.h"

class Game : IGame
{
public:
  Game();
  void start();
  virtual QWidget* window() override;
private:
  std::unique_ptr<GameWindow> game_window;
  std::unique_ptr<Map> map;
};

#endif // GAME_H
