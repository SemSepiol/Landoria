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
#include "../Menus/UpperMenu.h"

class GraphicsController : public IGraphicsControllerForWindow, public IGraphicsControllerForMap, public IGraphicsForUpperMenu
{
public:
  GraphicsController(class IGameForGraphic* game_controller);
  void start();
  virtual QWidget* window() const override;
//  virtual QWidget* window() const override {return window();}
  virtual Calculations* calculations() const override;

  void create_uppermenu();
  void create_map();
  void set_win_settings();

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

  virtual int width_menu() const override;
  virtual int height_menu() const override;
  virtual void exit() override;

private:
  void do_size_map();
  void do_contents();

  int _height_win;
  int _width_win;
  int _height_menu;
  int _width_menu;
  int _height_win_map;
  int _width_win_map;
  int _height_map;
  int _width_map;
  int num_cell_x;
  int num_cell_y;
  QPoint map_center;
  QPoint _win_map_center;

  IGameForGraphic* game_controller;

  std::unique_ptr<GameWindow> game_window;
  std::unique_ptr<UpperMenu> upper_menu;
  std::unique_ptr<Map> map;
  std::unique_ptr<Calculations> calc;
};

#endif // GRAPHICSCONTROLLER_H
