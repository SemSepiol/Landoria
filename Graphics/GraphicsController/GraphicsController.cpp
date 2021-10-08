#include "GraphicsController.h"
#include <iostream>

#include "windows.h"



GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}, minimap{new Minimap{game_window.get(), map.get(), this}}
{}

void GraphicsController::create_elements()
{
  AGraphicsController::create_elements();
  side_square_unit_menu = _size_win.width/20;
  create_minimap();
}

void GraphicsController::do_menu_unit(class Unit* unit, Position pos_cell)
{
  is_tracking_unit = true;
  tracking_unit = unit;
  pos_tracking_unit = pos_cell;

  Cell* cell = map->cell_by_indexes(pos_cell);
  unit_menu.reset(FactoryMenusUnit().create_menu(game_window.get(), this, unit, cell));
  unit_menu->set_geometry({0, _size_win.height - side_square_unit_menu * unit_menu->count_button() - _size_bottommenu.height},
                     side_square_unit_menu);
  unit_menu->hide();
  unit_menu->show();
}

void GraphicsController::do_menu_town(class Town* town)
{
  town_menu.reset(new MenuTown{this, town});
  town_menu->set_geometry({0, _size_uppermenu.height},
                          {_size_win.width, _size_win.height-_size_uppermenu.height});
  town_menu->hide();
  town_menu->show();
  upper_menu->set_enable_move_map(false);
}

void GraphicsController::move_unit(class Unit* unit, Position old_position, Position new_position)
{
  ControlContents controlcontents_old{map->cell_by_indexes({old_position})};
  ControlContents controlcontents_new{map->cell_by_indexes({new_position})};

  controlcontents_old.pop_content(unit);
  controlcontents_new.add_unit(unit);
  game_window->update();
}

class Building* GraphicsController::build(Buildings type_building, Position pos_cell)
{
  ControlContents controlcontents{map->cell_by_indexes(pos_cell)};
  if(controlcontents.has_building())
  {
    if(type_building == Buildings::Town && controlcontents.get_building() != Buildings::Town)
      controlcontents.del_building();
    else
      throw std::runtime_error("build: There is already a building in this cell");
  }
  IContent* content = controlcontents.add_building(type_building);
  class Building* building = static_cast<class Building*>(content);
  game_window->update();
  return building;
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
  else
    stop_check_move_unit();
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
  {
    if (content->what_content_I() == Contents::Unit)
      game_controller->current_player()->click_unit(static_cast<class Unit*>(content));
    else if (content->what_content_I() == Contents::Building)
    {
      class Building* building = static_cast<class Building*>(content);
      if(building->what_building_I() == Buildings::Town)
        game_controller->current_player()->click_town(static_cast<class Town*>(building));
    }
  }


  game_window->update();
}

class Unit* GraphicsController::add_unit(Units type_unit, Position pos_cell, int max_health, int max_movement)
{
  ControlContents controlcontents{map->cell_by_indexes(pos_cell)};
  class Unit* unit = static_cast<class Unit*>(controlcontents.add_unit(type_unit));
  unit->set_max_health(max_health);
  unit->set_health(max_health);
  unit->set_max_movement(max_movement);
  unit->set_movement(max_movement);
  return unit;
}

void GraphicsController::del_unit(class Unit* unit, Position pos_cell)
{
  ControlContents controlcontents{map->cell_by_indexes(pos_cell)};
  controlcontents.del_content(unit);
}

void GraphicsController::del_build(Position pos_cell)
{

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
   _map_center.setX(int(_size_map.width * coeffx));
   _map_center.setY(int(_size_map.height * coeffy));
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

  if(event->event == Events::Build)
  {
    BuildEvent* build_event = static_cast<BuildEvent*>(event);
    build_event->pos_cell = pos_tracking_unit;
  }

  game_controller->current_player()->menu_event(unit, event);
  del_menu_unit();
}

void GraphicsController::delete_townmenu()
{
  town_menu.reset();
  upper_menu->set_enable_move_map(true);
}

IMenuTownPlayer* GraphicsController::player()
{
  return game_controller->current_player()->menutown_player();
}

void GraphicsController::create_minimap()
{
  int width_minimap = _size_win.width/3;
  int height_minimap = _size_win.height/3;

  int hexagon_height1 = width_minimap/(int(num_cell.x)*2+1);
  int side1 = calc->my_round(hexagon_height1*2/sqrt(3));

  int side2 = height_minimap*2 / (3*int(num_cell.y)+1);

  hexagon_side_minimap = std::min(side1, side2);

  minimap->set_geometry(QPoint{_size_win.width, _size_win.height - _size_bottommenu.height}, hexagon_side_minimap);
  set_win_rect_minimap();
  minimap->hide();
}

void GraphicsController::set_win_rect_minimap()
{
  double coeffx = map_center_in_win_map().x()*1. / _size_map.width;
  double coeffy = map_center_in_win_map().y()*1. / _size_map.height;
  double coeff_width = _size_win_map.width*1. / _size_map.width;
  double coeff_height = _size_win_map.height*1. / _size_map.height;
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
  unit_menu.reset();
  is_tracking_unit = false;
  tracking_unit = nullptr;
}

void GraphicsController::unit_moved_to_cell(Cell* cell)
{
  Position pos_cell = map->indexes_by_cell(cell);
  if(!tracking_unit)
    throw std::runtime_error("click: unit_what_moving not set");
  FindUnitWay().get_way(tracking_unit, map.get(), pos_tracking_unit, pos_cell);

  MoveEvent* move_event = new MoveEvent{pos_cell};
  game_controller->current_player()->menu_event(tracking_unit, move_event);
  stop_check_move_unit();
  del_menu_unit();
}

