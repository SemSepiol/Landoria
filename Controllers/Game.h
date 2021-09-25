#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <QApplication>

#include "IGame.h"
#include "../Graphics/GraphicsController/GraphicsController.h"
#include "Player.h"

class Game : public IGameForGraphic, public IGameForPlayer
{
public:
  Game(QApplication* app, int count_cell_x, int count_cell_y, size_t count_players);
  void start();

  virtual int count_cell_x() const override;
  virtual int count_cell_y() const override;
  virtual int width_win() const override;
  virtual int height_win() const override;
  virtual void exit() override {}
  virtual IPlayer* current_player() const override;

  virtual IGraphicsControllerForPlayer* graphics_controller() const override;
private:
  void do_players(size_t count_player);

  std::unique_ptr<GraphicsController> _graphics_controller;
  std::vector<std::unique_ptr<Player>> players;
  size_t _current_player;

  int _count_cell_x;
  int _count_cell_y;
  int _width_win;
  int _height_win;
};

#endif // GAME_H
