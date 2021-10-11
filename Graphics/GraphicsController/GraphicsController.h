#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>

#include "AGraphicsController.h"
#include "../Units/Unit.h"
#include "EventsStructures.h"
#include "../Cell.h"
#include "../Factories/FactoryMenusUnit.h"
#include "../Minimap.h"
#include "../../Controllers/FindUnitWay.h"
#include "../DrawWay.h"
#include "../MenuTown/MenuTown.h"

class GraphicsController : public AGraphicsController, public IPlayerGraphicsController,
    public IUnitMenuGraphicsController
{
public:
  GraphicsController(IGameForGraphic* game_controller);
  virtual void create_elements() override;

  virtual void start_check_move_unit() override;
  virtual void stop_check_move_unit(QPoint mouse_pos) override;
  virtual void move_mouse(QPoint new_pos) override;
  virtual void click(QPoint pos) override;
  virtual class Unit* add_unit(Units unit, Position pos_cell) override;

  virtual void move_unit(class Unit* unit, Position old_position, Position new_position) override;
  virtual class Building* build(Buildings building, Position pos_cell) override;
  virtual void del_build(Position pos_cell) override;
  virtual void del_unit(class Unit* unit, Position pos_cell) override;
  virtual void do_menu_unit(class Unit* unit, Position pos_cell) override;
  virtual void do_menu_town(PlayerTown* town) override;
  virtual void centering_by_cell(Position pos_cell) override;
  virtual void highlight_unit(class Unit* unit, Position pos) override;
  virtual void draw_playermap(PlayerMap* playermap) override;
  virtual Map* map() const override;

  virtual void draw_elements() override;
  virtual void move_map(QPoint move_point) override;
  virtual void resize_map(double coefficient) override;

  /* coeffx = new_map_center.x / width_map
     coeffy = new_map_center.y / height_map */
  virtual void move_map(double coeffx, double coeffy) override;

  virtual void menu_unit_event(class Unit* unit, Event* event) override;

  virtual void delete_townmenu() override;
  virtual void show_minimap() override;
  virtual void next_move() override;
private:
  void create_minimap();
  void set_win_rect_minimap();
  void no_highlight_unit(class Unit* unit, Position pos);

  void start_check_move_unit(class Unit* unit);
  void stop_check_move_unit();
  void del_menu_unit();
  void unit_moved_to_cell(Cell* cell);
  bool is_tracking_unit = false;
  bool is_moving_unit = false;
  class Unit* tracking_unit = nullptr;
  Position pos_tracking_unit;

  int side_square_unit_menu;
  int hexagon_side_minimap;

  Cell* click_cell = nullptr;
  std::unique_ptr<DrawWay> drawway{nullptr};
  std::unique_ptr<AMenuForUnit> unit_menu{nullptr};
  std::unique_ptr<MenuTown> town_menu{nullptr};
  std::unique_ptr<Minimap> minimap;
};

#endif // GRAPHICSCONTROLLER_H
