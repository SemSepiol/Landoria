#ifndef AGRAPHICSCONTROLLER_H
#define AGRAPHICSCONTROLLER_H

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
#include "../Menus/BottomMenu.h"

class AGraphicsController : public IGraphicsControllerForWindow, public IGraphicsControllerForMap,
    public IGraphicsControllerForMenuInWindow, public IGraphicsControllerForMiniMap
{
public:
  AGraphicsController(IGameForGraphic* game_controller);
  void start();
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual void create_elements();

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
  virtual void exit() override;

protected:
  // Возвращает центр кары относительно центра окна карты
  QPoint map_center_in_win_map();
  void create_uppermenu();
  void create_bottommenu();
  void create_map();
  void set_win_settings();
  void control_pos_map();

  void do_size_map();

  int _height_win;
  int _width_win;
  int _height_uppermenu;
  int _width_uppermenu;
  int _height_bottommenu;
  int _width_bottommenu;
  int _height_win_map;
  int _width_win_map;
  int _height_map;
  int _width_map;
  int num_cell_x;
  int num_cell_y;
  QPoint map_center;
  QPoint _win_map_center;
  QPoint _uppermenu_top_left = {0,0};

  IGameForGraphic* game_controller;

  std::unique_ptr<GameWindow> game_window;
  std::unique_ptr<UpperMenu> upper_menu;
  std::unique_ptr<BottomMenu> bottom_menu;
  std::unique_ptr<Map> map;
  std::unique_ptr<Calculations> calc;
};

#endif // AGRAPHICSCONTROLLER_H
