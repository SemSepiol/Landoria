#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include "AGraphicsController.h"
#include "../Units/Unit.h"
#include "EventsStructures.h"
#include "../Cell.h"


class GraphicsController : public AGraphicsController
{
public:
  GraphicsController(IGameForGraphic* game_controller);
  Event* menu_unit(class Unit* unit);
  virtual void move_unit(class Unit* unit, size_t old_position_x, size_t old_position_y,
                         size_t new_position_x, size_t new_position_y) override;

  virtual void click(QPoint pos) override;
  virtual class Unit* add_unit(Units unit, size_t cell_x, size_t cell_y) override;

private:
  bool is_there_menu = false;

  Cell* click_cell = nullptr;
};

#endif // GRAPHICSCONTROLLER_H
