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

class AGraphicsController : public IWindowGraphicsController, public IMapGraphicsController,
    public IMenuInWindowGraphicsController, public IMiniMapGraphicsController, public ITownMenuGraphicsController
{
public:
  AGraphicsController(IGameForGraphic* game_controller);
  void start();
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual void create_elements();

  virtual size_t count_cell_x() const override;
  virtual size_t count_cell_y() const override;

  virtual Size size_win() const override;
  virtual Size size_win_map() const override;
  virtual Size size_map() const override;
  virtual QPoint win_map_center() const override;
  virtual QPoint map_center() const override;

  virtual void draw_elements() override;
  virtual void move_map(QPoint move_point) override;
  virtual void move_map(double coeffx, double coeffy) override = 0;
  virtual void resize_map(double coefficient) override;
  virtual int map_upper_edge() const override;
  virtual int map_bottom_edge() const override;
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

  Size _size_win;
  Size _size_uppermenu;
  Size _size_bottommenu;
  Size _size_win_map;
  Size _size_map;
  Position num_cell;
  QPoint _map_center;
  QPoint _win_map_center;
  QPoint _uppermenu_top_left = {0,0};

  IGameForGraphic* game_controller;

  std::unique_ptr<GameWindow> game_window;
  std::unique_ptr<UpperMenu> upper_menu;
  std::unique_ptr<BottomMenu> bottom_menu;
  std::unique_ptr<Map> _map;
  std::unique_ptr<Calculations> calc;
};

#endif // AGRAPHICSCONTROLLER_H
