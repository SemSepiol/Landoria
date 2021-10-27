#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <QApplication>

#include "IGame.h"
#include "../Graphics/GraphicsController/GraphicsController.h"
#include "Player/Player.h"

class Game : public IGameForGraphic, public IGameForPlayer, public IGameForWidget
{
public:
  Game(QApplication* app, size_t count_cell_x, size_t count_cell_y, size_t count_players);
  void start();

  virtual size_t count_cell_x() const override;
  virtual size_t count_cell_y() const override;
  virtual int width_win() const override;
  virtual int height_win() const override;
  virtual void exit() override {}
  virtual void next_move() override;
  virtual IPlayer* current_player() const override;
  virtual IGameForWidget* igame_for_widget() override;

  virtual IPlayerGraphicsController* graphics_controller() const override;

  virtual void start_move() override;
  virtual QWidget* window() const override;
private:
  void do_players(size_t count_player);
  size_t num_curr_player();
  void do_start_inform();

  std::unique_ptr<GraphicsController> _graphics_controller;
  std::vector<std::unique_ptr<Player>> players;
  Player* _current_player;

  size_t _count_cell_x;
  size_t _count_cell_y;
  int _width_win;
  int _height_win;
};

#endif // GAME_H
