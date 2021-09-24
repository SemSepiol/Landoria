#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>
#include <QWidget>
#include <QPoint>

#include "IGraphicsController.h"
#include "Calculations.h"
#include "../GameWindow.h"
#include "../Map.h"
#include "../Cell.h"
#include "CreateMap.h"
#include "../../Controllers/IGame.h"

class GraphicsController : public IGraphicsControllerForWindow, public IGraphicsControllerForMap
{
public:
  GraphicsController(class IGame* game_controller, int count_cell_x, int count_cell_y);
  void start();
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual int count_cell_x() const override;
  virtual int count_cell_y() const override;

  virtual int width_win() const override;
  virtual int height_win() const override;
  virtual int width_win_map() const override;
  virtual int height_win_map() const override;
  virtual int width_map() const override;
  virtual int height_map() const override;
  virtual QPoint win_map_center() const override;

  virtual void draw_map() override;
  virtual void move_map(QPoint move_point) override;
  virtual void resize_map(double coefficient) override;
  virtual void resize_win(const QSize& new_size) override;
  virtual void click(QPoint pos) override;

private:
  void create_map();
  void do_size_map();
  void do_contents();

  int _height_win;
  int _width_win;
  int _height_win_map;
  int _width_win_map;
  int _height_map;
  int _width_map;
  int num_cell_x;
  int num_cell_y;
  QPoint map_center;
  QPoint _win_map_center;

  IGame* game_controller;

  std::unique_ptr<GameWindow> game_window;
  std::unique_ptr<Map> map;
  std::unique_ptr<Calculations> calc;
};

#endif // GRAPHICSCONTROLLER_H
