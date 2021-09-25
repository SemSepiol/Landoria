#ifndef GAME_H
#define GAME_H

#include <memory>
#include <QApplication>

#include "IGame.h"
#include "../Graphics/GraphicsController/GraphicsController.h"

class Game : public IGameForGraphic
{
public:
  Game(QApplication* app, int count_cell_x, int count_cell_y);
  void start();

  virtual int count_cell_x() const override;
  virtual int count_cell_y() const override;
  virtual int width_win() const override;
  virtual int height_win() const override;
  virtual void exit() override {}
private:
  std::unique_ptr<GraphicsController> graphics_controller;

  int _count_cell_x;
  int _count_cell_y;
  int _width_win;
  int _height_win;
};

#endif // GAME_H
