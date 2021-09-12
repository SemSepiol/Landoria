#ifndef GAME_H
#define GAME_H

#include <memory>
#include <QWidget>
#include <QPoint>

#include "IGame.h"
#include "Calculations.h"
#include "../Graphics/GameWindow.h"
#include "../Graphics/Map.h"

class Game : IGame
{
public:
  Game();
  void start();
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual int count_cell_x() const override;
  virtual int count_cell_y() const override;

  virtual int width_win() const override;
  virtual int height_win() const override;
  virtual int width_map() const override;
  virtual int height_map() const override;

  virtual void draw_map() override;
private:
  QPoint center_window() const;

  int _height_win;
  int _width_win;
  int num_cell_x;
  int num_cell_y;

  std::unique_ptr<GameWindow> game_window;
  std::unique_ptr<Map> map;
  std::unique_ptr<Calculations> calc;
};

#endif // GAME_H
