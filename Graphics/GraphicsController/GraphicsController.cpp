#include "GraphicsController.h"
#include <iostream>

GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}
{

}

Event* GraphicsController::menu_unit(class Unit* unit)
{

}

void GraphicsController::move_unit(class Unit* unit, size_t old_position_x, size_t old_position_y,
                                   size_t new_position_x, size_t new_position_y)
{
  ControlContents controlcontents_old{map->cell_by_index(old_position_x, old_position_y)};
  ControlContents controlcontents_new{map->cell_by_index(new_position_x, new_position_y)};

//  std::cout << unit << std::endl;
  controlcontents_old.pop_content(unit);
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


  if (content->what_content_I() == Contents::Unit)
    game_controller->current_player()->click_unit(static_cast<class Unit*>(content));

  game_window->update();
}

class Unit* GraphicsController::add_unit(Units unit, size_t cell_x, size_t cell_y)
{
  ControlContents controlcontents{map->cell_by_index(cell_x, cell_y)};
  return static_cast<class Unit*>(controlcontents.add_unit(unit));
}
