#include "GraphicsController.h"
#include <iostream>

#include "windows.h"



GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}, minimap{new Minimap{game_window.get(), map.get(), this}}
{}

void GraphicsController::create_elements()
{
  AGraphicsController::create_elements();
  side_square_unit_menu = _width_win/20;
  create_minimap();
}

void GraphicsController::do_menu_unit(class Unit* unit, size_t position_x, size_t position_y)
{
  is_tracking_unit = true;
  tracking_unit = unit;
  pos_tracking_unit = {position_x, position_y};

  Cell* cell = map->cell_by_indexes(position_x, position_y);
  menu_for_unit.reset(FactoryMenusUnit().create_menu(game_window.get(), this, unit, cell));
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

void GraphicsController::start_check_move_unit()
{
  if(tracking_unit)
    start_check_move_unit(tracking_unit);
}

void GraphicsController::stop_check_move_unit(QPoint mouse_pos)
{
  if(!tracking_unit)
    return;

  auto pair = map->click(mouse_pos - _map_center);
  Cell* cell = pair.first;
  if(cell)
    unit_moved_to_cell(cell);
}

void GraphicsController::move_mouse(QPoint new_pos)
{
  if(is_moving_unit)
  {
    auto pair = map->click(new_pos - _map_center);
    Cell* cell = pair.first;
    if(!cell)
    {
      return;
    }
    Position end_way = map->indexes_by_cell(pair.first);
    if(drawway)
      drawway->set_end_way(end_way);
    game_window->update();
  }

}

void GraphicsController::click(QPoint pos)
{
  auto pair = map->click(pos - _map_center);
  Cell* cell = pair.first;
  IContent* content = pair.second;


  if(is_moving_unit)
  {
    unit_moved_to_cell(cell);
    return;
  }

  del_menu_unit();
  if(content)
    if (content->what_content_I() == Contents::Unit)
      game_controller->current_player()->click_unit(static_cast<class Unit*>(content));

  game_window->update();
}

class Unit* GraphicsController::add_unit(Units type_unit, size_t cell_x, size_t cell_y, int max_health, int max_movement)
{
  ControlContents controlcontents{map->cell_by_indexes(cell_x, cell_y)};
  class Unit* unit = static_cast<class Unit*>(controlcontents.add_unit(type_unit));
  unit->set_max_health(max_health);
  unit->set_health(max_health);
  unit->set_max_movement(max_movement);
  unit->set_movement(max_movement);
  return unit;
}

void GraphicsController::del_unit(class Unit* unit, size_t cell_x, size_t cell_y)
{
  ControlContents controlcontents{map->cell_by_indexes(cell_x, cell_y)};
  controlcontents.del_content(unit);
}

void GraphicsController::draw_elements()
{
  AGraphicsController::draw_elements();
  if(drawway.get()){
//    std::cout << "draw way" << std::endl;
    drawway->draw();
  }
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
   _map_center.setX(int(_width_map * coeffx));
   _map_center.setY(int(_height_map * coeffy));
   control_pos_map();
   set_win_rect_minimap();
   game_window->update();
}

void GraphicsController::menu_unit_event(class Unit* unit, Event* event)
{
  if(event->event == Events::Move)
  {
    if(is_moving_unit)
      stop_check_move_unit();
    else
      start_check_move_unit(unit);
    return;
  }
  game_controller->current_player()->menu_event(unit, event);
  del_menu_unit();
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
  is_moving_unit = true;
  drawway.reset(new DrawWay{game_window.get(), map.get(), pos_tracking_unit, unit});
}

void GraphicsController::stop_check_move_unit()
{
  drawway.reset();
  is_moving_unit = false;
  game_window->update();
}

void GraphicsController::del_menu_unit()
{
  menu_for_unit.reset();
  is_tracking_unit = false;
  tracking_unit = nullptr;
}

void GraphicsController::unit_moved_to_cell(Cell* cell)
{
  auto pair_of_ind = map->indexes_by_cell(cell);
  if(!tracking_unit)
    throw std::runtime_error("click: unit_what_moving not set");
  FindUnitWay().get_way(tracking_unit, map.get(), pos_tracking_unit, {pair_of_ind});

  MoveEvent* move_event = new MoveEvent{pair_of_ind.first, pair_of_ind.second};
  game_controller->current_player()->menu_event(tracking_unit, move_event);
  stop_check_move_unit();
  del_menu_unit();
}

