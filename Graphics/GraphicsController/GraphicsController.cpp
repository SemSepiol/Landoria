#include "GraphicsController.h"

GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}
{

}

Event* GraphicsController::menu_unit(class Unit* unit)
{

}

void GraphicsController::move_unit(class Unit* unit, Cell* old_position, Cell* new_position)
{
  ControlContents controlcontents_old{old_position};
  controlcontents_old.del_content(unit);

  ControlContents controlcontents_new{new_position};
  controlcontents_new.add_unit(unit);
}

void GraphicsController::click(QPoint pos)
{
  //  if (!is_there_menu)
  //  {
  //    AGraphicsController::click(pos);
  //    return;
  //  }

  auto pair = map->click(pos - map_center);
  Cell* cell = pair.first;
  IContent* content = pair.second;

}
