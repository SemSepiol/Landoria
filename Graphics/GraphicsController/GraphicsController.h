#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>
#include <QPoint>
#include <QWidget>

#include "IGraphicsController.h"
#include "MapGraphicsController.h"
#include "MenuGraphicsController.h"
#include "PlayerGraphicsController.h"
#include "WindowGraphicsController.h"


class GraphicsController : public IGraphicsController
{
public:
  GraphicsController(IGameForGraphic* game_controller);
  QWidget* window() const;
  void start();
  void do_start_inform(QString string);
  void del_start_inform();
  virtual void create_elements();

  virtual Size& get_size_win() override;
  virtual Size& get_size_uppermenu() override;
  virtual Size& get_size_bottommenu() override;
  virtual Size& get_size_win_map() override;
  virtual Size& get_size_map() override;
  virtual Position& get_num_cell() override;
  virtual QPoint& get_map_center() override;
  virtual QPoint& get_win_map_center() override;
  virtual bool& get_enabled_map() override;

  virtual IGameForGraphic* get_game_controller() override;

  virtual GameWindow* get_game_window() override;
  virtual UpperMenu* get_upper_menu() override;
  virtual BottomMenu* get_bottom_menu() override;
  virtual Map* get_map() override;
  virtual Calculations* get_calc() override;

  virtual bool& get_is_tracking_unit() override;
  virtual bool& get_is_moving_unit() override;
  virtual class Unit*& get_tracking_unit() override;
  virtual Position& get_pos_tracking_unit() override;

  virtual int& get_side_square_unit_menu() override;
  virtual int& get_hexagon_side_minimap() override;

  virtual DrawWay* get_drawway() override;
  virtual void set_drawway(DrawWay* drawway) override;

  virtual AMenuForUnit* get_unit_menu() override;
  virtual void set_unit_menu(AMenuForUnit* unit_menu) override;

  virtual UnitInformation* get_unit_information() override;
  virtual void set_unit_information(UnitInformation* unit_information) override;

  virtual MenuTown* get_town_menu() override;
  virtual void set_town_menu(MenuTown*) override;

  virtual Minimap* get_minimap() override;

  virtual StartMoveInform* get_start_move_inform() override;

  virtual IWindowGraphicsControllerFull* get_iwindow_gc_full() override;
  virtual IMenuGraphicsControllerFull* get_imenu_gc_full() override;
  virtual IPlayerGraphicsController* get_iplayer_gc() override;
  virtual IMapGraphicsControllerFull* get_imap_gc_full() override;

protected:
  Size _size_win;
  Size _size_uppermenu;
  Size _size_bottommenu;
  Size _size_win_map;
  Size _size_map;
  Position num_cell;
  QPoint _map_center;
  QPoint _win_map_center;
  bool enabled_map = true;

  IGameForGraphic* game_controller;

  std::unique_ptr<MapGraphicsController> map_gc;
  std::unique_ptr<WindowGraphicsController> window_gc;
  std::unique_ptr<PlayerGraphicsController> player_gc;
  std::unique_ptr<MenuGraphicsController> menu_gc;

  std::unique_ptr<GameWindow> game_window;
  std::unique_ptr<UpperMenu> upper_menu;
  std::unique_ptr<BottomMenu> bottom_menu;
  std::unique_ptr<Map> _map;
  std::unique_ptr<Calculations> calc;

  bool is_tracking_unit = false;
  bool is_moving_unit = false;
  class Unit* tracking_unit = nullptr;
  Position pos_tracking_unit;

  int side_square_unit_menu;
  int hexagon_side_minimap;

  Cell* click_cell = nullptr;
  std::unique_ptr<DrawWay> drawway{nullptr};
  std::unique_ptr<AMenuForUnit> unit_menu{nullptr};
  std::unique_ptr<UnitInformation> unit_information{nullptr};
  std::unique_ptr<MenuTown> town_menu{nullptr};
  std::unique_ptr<Minimap> minimap;
  std::unique_ptr<StartMoveInform> start_move_inform;
};

#endif // GRAPHICSCONTROLLER_H
