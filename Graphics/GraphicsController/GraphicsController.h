#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <memory>

#include "AGraphicsController.h"
#include "../Units/Unit.h"
#include "EventsStructures.h"
#include "../Cell.h"
#include "../Factories/FactoryMenusUnit.h"


class GraphicsController : public AGraphicsController
{
public:
  GraphicsController(IGameForGraphic* game_controller);
  virtual void create_elements() override;
  virtual void do_menu_unit(IPlayerForMenu* player, class Unit*) override;
  virtual void move_unit(class Unit* unit, size_t old_position_x, size_t old_position_y,
                         size_t new_position_x, size_t new_position_y) override;

  virtual void click(QPoint pos) override;
  virtual class Unit* add_unit(Units unit, size_t cell_x, size_t cell_y) override;
  virtual void del_unit(class Unit* unit, size_t cell_x, size_t cell_y) override;
private:
  int side_square_unit_menu;

  Cell* click_cell = nullptr;
  std::unique_ptr<AMenu> menu{nullptr};
};

#endif // GRAPHICSCONTROLLER_H
