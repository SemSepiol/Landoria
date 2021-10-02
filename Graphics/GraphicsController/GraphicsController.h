#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>

#include "AGraphicsController.h"
#include "../Units/Unit.h"
#include "EventsStructures.h"
#include "../Cell.h"
#include "../Factories/FactoryMenusUnit.h"
#include "../Minimap.h"


class GraphicsController : public AGraphicsController, public IGraphicsControllerForPlayer,
    public IGraphicsControllerMenuForUnit
{
public:
  GraphicsController(IGameForGraphic* game_controller);
  virtual void create_elements() override;
  virtual void do_menu_unit(class Unit*) override;
  virtual void move_unit(class Unit* unit, size_t old_position_x, size_t old_position_y,
                         size_t new_position_x, size_t new_position_y) override;
  virtual void build(Buildings building, size_t position_x, size_t position_y) override;


  virtual void click(QPoint pos) override;
  virtual class Unit* add_unit(Units unit, size_t cell_x, size_t cell_y) override;
  virtual void del_unit(class Unit* unit, size_t cell_x, size_t cell_y) override;

  virtual void move_map(QPoint move_point) override;
  virtual void resize_map(double coefficient) override;

  /* coeffx = new_map_center.x / width_map
     coeffy = new_map_center.y / height_map */
  virtual void move_map(double coeffx, double coeffy) override;

  virtual void menu_unit_event(class Unit* unit, Event* event) override;
private:
  void create_minimap();
  void set_win_rect_minimap();

  virtual void show_minimap() override;

  void start_check_move_unit(class Unit* unit);
  void stop_check_move_unit();
  void unit_moved(Cell* cell);
  bool is_checking_move_unit = false;
  class Unit* unit_what_moving = nullptr;

  int side_square_unit_menu;
  int hexagon_side_minimap;

  Cell* click_cell = nullptr;
  std::unique_ptr<AMenuForUnit> menu_for_unit{nullptr};
  std::unique_ptr<Minimap> minimap;
};

#endif // GRAPHICSCONTROLLER_H
