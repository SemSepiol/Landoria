#include "GraphicsController.h"
#include <iostream>

GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}
{
}

void GraphicsController::create_elements()
{
  AGraphicsController::create_elements();
  side_square_unit_menu = _width_win/20;
}

void GraphicsController::do_menu_unit(IPlayerForMenu* player, class Unit* unit)
{
  menu.reset(FactoryMenusUnit().create_menu(game_window.get(), player, unit));
  menu->set_geometry({0, _height_win - side_square_unit_menu * menu->count_button()},
                     side_square_unit_menu);
  menu->hide();
  menu->show();
}

void GraphicsController::move_unit(class Unit* unit, size_t old_position_x, size_t old_position_y,
                                   size_t new_position_x, size_t new_position_y)
{
  ControlContents controlcontents_old{map->cell_by_indexes(old_position_x, old_position_y)};
  ControlContents controlcontents_new{map->cell_by_indexes(new_position_x, new_position_y)};

  controlcontents_old.pop_content(unit);
  controlcontents_new.add_unit(unit);
}

void GraphicsController::click(QPoint pos)
{
  if (menu.get())
    menu.reset();
  auto pair = map->click(pos - map_center);
  Cell* cell = pair.first;
  IContent* content = pair.second;

  if(content)
    if (content->what_content_I() == Contents::Unit)
      game_controller->current_player()->click_unit(static_cast<class Unit*>(content));

  game_window->update();
}

class Unit* GraphicsController::add_unit(Units unit, size_t cell_x, size_t cell_y)
{
  ControlContents controlcontents{map->cell_by_indexes(cell_x, cell_y)};
  return static_cast<class Unit*>(controlcontents.add_unit(unit));
}

void GraphicsController::del_unit(class Unit* unit, size_t cell_x, size_t cell_y)
{
  ControlContents controlcontents{map->cell_by_indexes(cell_x, cell_y)};
  controlcontents.del_content(unit);
}
