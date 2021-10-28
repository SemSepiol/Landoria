#include "GraphicsController.h"
#include <iostream>

#include "windows.h"


GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}, minimap{new Minimap{game_window.get(), _map.get(), this}},
    player_gc{new PlayerGraphicsController(this)}
{}

void GraphicsController::do_start_inform(QString string)
{
  start_move_inform.reset(new StartMoveInform(game_controller->igame_for_widget(), string,
                                              QPoint{_size_win.width/2, _size_win.height/2}));
  Size size{_size_win.width/3, _size_win.height/3};
  start_move_inform->set_geometry(QPoint{_size_win.width/2 - size.width/2, _size_win.height/2 - size.height/2}, size);
  start_move_inform->hide();
  start_move_inform->show();
  start_move_inform->raise();
  enabled_map = false;
}

void GraphicsController::del_start_inform()
{
  start_move_inform.reset();
  enabled_map = true;
}

void GraphicsController::press_enter()
{
  if(start_move_inform)
    game_controller->start_move();
}

void GraphicsController::create_elements()
{
  AGraphicsController::create_elements();
  side_square_unit_menu = _size_win.width/20;
  create_minimap();
}


void GraphicsController::no_highlight_unit(class Unit* unit, Position pos_cell)
{
  ControlContents controlcontents{_map->cell_by_indexes(pos_cell)};
  controlcontents.set_highlight_unit(unit, false);
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

  auto pair = _map->click(mouse_pos - _map_center);
  Cell* cell = pair.first;
  if(cell)
    unit_moved_to_cell(cell);
  else
    stop_check_move_unit();
}

void GraphicsController::move_mouse(QPoint new_pos)
{
  if(!enabled_map)
    return;

  auto pair = _map->click(new_pos - _map_center);
  Cell* cell = pair.first;
  if(!cell)
    return;
  bottom_menu->update_infofm(cell);

  if(is_moving_unit)
  {
    Position end_way = _map->indexes_by_cell(pair.first);
    if(drawway)
      drawway->set_end_way(end_way);
    game_window->update();
  }
}

void GraphicsController::click(QPoint pos)
{
  if(!enabled_map)
    return;

  auto pair = _map->click(pos - _map_center);
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

void GraphicsController::draw_elements()
{
  AGraphicsController::draw_elements();
  if(drawway.get())
    drawway->draw();
}

void GraphicsController::move_map(QPoint move_point)
{
  if(!enabled_map)
    return;

  AGraphicsController::move_map(move_point);
  set_win_rect_minimap();
}

void GraphicsController::resize_map(double coefficient, QPoint pos_mouse)
{
  if(!enabled_map)
    return;

  AGraphicsController::resize_map(coefficient, pos_mouse);
  set_win_rect_minimap();
  game_window->update();
}

void GraphicsController::move_map(double coeffx, double coeffy)
{
  if(!enabled_map)
    return;

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
//  no_highlight_unit(unit)
}

void GraphicsController::delete_townmenu()
{
  town_menu.reset();
  upper_menu->set_enable_move_map(true);
  bottom_menu->show();

  enabled_map = true;
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

void GraphicsController::next_move()
{
  game_controller->next_move();
}

void GraphicsController::do_inform_widget(QString text)
{
  game_window->do_inform_widget(text);
}

void GraphicsController::del_inform_widget()
{
  game_window->del_inform_widget();
}

bool& GraphicsController::get_is_tracking_unit()
{
  return is_tracking_unit;
}

bool& GraphicsController::get_is_moving_unit()
{
  return is_moving_unit;
}

class Unit*& GraphicsController::get_tracking_unit()
{
  return tracking_unit;
}

Position& GraphicsController::get_pos_tracking_unit()
{
  return pos_tracking_unit;
}

int& GraphicsController::get_side_square_unit_menu()
{
  return side_square_unit_menu;
}

int& GraphicsController::get_hexagon_side_minimap()
{
  return hexagon_side_minimap;
}

DrawWay* GraphicsController::get_drawway()
{
  return drawway.get();
}

AMenuForUnit* GraphicsController::get_unit_menu()
{
  return unit_menu.get();
}

void GraphicsController::set_unit_menu(AMenuForUnit* _unit_menu)
{
  unit_menu.reset(_unit_menu);
}

UnitInformation* GraphicsController::get_unit_information()
{
  return unit_information.get();
}

void GraphicsController::set_unit_information(UnitInformation* _unit_information)
{
  unit_information.reset(_unit_information);
}

MenuTown* GraphicsController::get_town_menu()
{
  return town_menu.get();
}

void GraphicsController::set_town_menu(MenuTown* _town_menu)
{
  town_menu.reset(_town_menu);
}

Minimap* GraphicsController::get_minimap()
{
  return minimap.get();
}

StartMoveInform* GraphicsController::get_start_move_inform()
{
  return start_move_inform.get();
}

IUnitMenuGraphicsController* GraphicsController::get_iunit_menu_gc()
{
  return this;
}

ITownMenuGraphicsController* GraphicsController::get_itown_menu_gc()
{
  return this;
}

IPlayerGraphicsController* GraphicsController::get_iplayer_gc()
{
  return player_gc.get();
}

void GraphicsController::start_check_move_unit(class Unit* unit)
{
  is_moving_unit = true;
  drawway.reset(new DrawWay{game_window.get(), _map.get(), pos_tracking_unit, unit});
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
  unit_information.reset();
  no_highlight_unit(tracking_unit, pos_tracking_unit);
  is_tracking_unit = false;
  tracking_unit = nullptr;
}

void GraphicsController::unit_moved_to_cell(Cell* cell)
{
  Position pos_cell = _map->indexes_by_cell(cell);
  if(!tracking_unit)
    throw std::runtime_error("click: unit_what_moving not set");
  FindUnitWay().get_way(tracking_unit, _map.get(), pos_tracking_unit, pos_cell);

  MoveEvent* move_event = new MoveEvent{pos_cell};
  game_controller->current_player()->menu_event(tracking_unit, move_event);
  stop_check_move_unit();
  del_menu_unit();
}

