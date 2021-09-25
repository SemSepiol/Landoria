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
  void move_unit(class Unit* unit, Cell* old_position, Cell* new_position);

  virtual void click(QPoint pos) override;

private:
  bool is_there_menu = false;

  Cell* click_cell = nullptr;
};

#endif // GRAPHICSCONTROLLER_H
