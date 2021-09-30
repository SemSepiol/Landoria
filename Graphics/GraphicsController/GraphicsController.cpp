#include "GraphicsController.h"
#include <iostream>

GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}, minimap{new Minimap{game_window.get(), map.get(), this}}
{
}

void GraphicsController::create_elements()
{
  AGraphicsController::create_elements();
  side_square_unit_menu = _width_win/20;
  create_minimap();
}

void GraphicsController::do_menu_unit(IPlayerForMenu* player, class Unit* unit)
{
  menu.reset(FactoryMenusUnit().create_menu(game_window.get(), player, unit));
  menu->set_geometry({0, _height_win - side_square_unit_menu * menu->count_button() - _height_bottommenu},
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
//  Cell* cell = pair.first;
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

void GraphicsController::move_map(QPoint move_point)
{
  AGraphicsController::move_map(move_point);
  set_win_rect_minimap();
}

void GraphicsController::resize_map(double coefficient)
{
  AGraphicsController::resize_map(coefficient);
  set_win_rect_minimap();
  game_window->update();
}

void GraphicsController::move_map(double coeffx, double coeffy)
{
   map_center.setX(int(_width_map * coeffx));
   map_center.setY(int(_height_map * coeffy));
   control_pos_map();
   set_win_rect_minimap();
   game_window->update();
}

void GraphicsController::create_minimap()
{
  int width_minimap = _width_win/3;
  int height_minimap = _height_win/3;

  int hexagon_height1 = width_minimap/(num_cell_x*2+1);
  int side1 = calc->my_round(hexagon_height1*2/sqrt(3));

  int side2 = height_minimap*2 / (3*num_cell_y+1);

  hexagon_side_minimap = std::min(side1, side2);

  minimap->set_geometry(QPoint{_width_win, _height_win - _height_bottommenu}, hexagon_side_minimap);
  set_win_rect_minimap();
  minimap->hide();
}

void GraphicsController::set_win_rect_minimap()
{
  double coeffx = map_center_in_win_map().x()*1. / _width_map;
  double coeffy = map_center_in_win_map().y()*1. / _height_map;
  double coeff_width = _width_win_map*1. / _width_map;
  double coeff_height = _height_win_map*1. / _height_map;
  minimap->set_win_rect(coeffx, coeffy, coeff_width, coeff_height);
}

void GraphicsController::show_minimap()
{
  if(minimap->isVisible())
    minimap->hide();
  else
    minimap->show();
}
