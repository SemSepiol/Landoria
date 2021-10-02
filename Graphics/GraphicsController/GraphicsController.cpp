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

void GraphicsController::do_menu_unit(class Unit* unit)
{
  menu_for_unit.reset(FactoryMenusUnit().create_menu(game_window.get(), this, unit));
  menu_for_unit->set_geometry({0, _height_win - side_square_unit_menu * menu_for_unit->count_button() - _height_bottommenu},
                     side_square_unit_menu);
  menu_for_unit->hide();
  menu_for_unit->show();
}

void GraphicsController::move_unit(class Unit* unit, size_t old_position_x, size_t old_position_y,
                                   size_t new_position_x, size_t new_position_y)
{
  ControlContents controlcontents_old{map->cell_by_indexes(old_position_x, old_position_y)};
  ControlContents controlcontents_new{map->cell_by_indexes(new_position_x, new_position_y)};

  controlcontents_old.pop_content(unit);
  controlcontents_new.add_unit(unit);
  game_window->update();
}

void GraphicsController::build(Buildings building, size_t position_x, size_t position_y)
{
  ControlContents controlcontents{map->cell_by_indexes(position_x, position_y)};
  if(controlcontents.has_building())
    throw std::runtime_error("build: There is already a building in this cell");
  controlcontents.add_building(building);
  game_window->update();
}

void GraphicsController::click(QPoint pos)
{
  auto pair = map->click(pos - map_center);
  Cell* cell = pair.first;
  IContent* content = pair.second;

  if(is_checking_move_unit)
  {
    unit_moved(cell);
    return;
  }

  menu_for_unit.reset();
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

void GraphicsController::menu_unit_event(class Unit* unit, Event* event)
{
  if(event->event == Events::Move)
  {
    if(is_checking_move_unit)
      stop_check_move_unit();
    else
      start_check_move_unit(unit);
    return;
  }
  game_controller->current_player()->menu_event(unit, event);
  menu_for_unit.reset();
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

void GraphicsController::start_check_move_unit(class Unit* unit)
{
  unit_what_moving = unit;
  is_checking_move_unit = true;
}

void GraphicsController::stop_check_move_unit()
{
  is_checking_move_unit = false;
  unit_what_moving = nullptr;
}

void GraphicsController::unit_moved(Cell* cell)
{
  auto pair_of_ind = map->indexes_by_cell(cell);
  if(!unit_what_moving)
    throw std::runtime_error("click: unit_what_moving not set");
  Move_event* move_event = new Move_event{pair_of_ind.first, pair_of_ind.second};
  game_controller->current_player()->menu_event(unit_what_moving, move_event);
  stop_check_move_unit();
  menu_for_unit.reset();
}
