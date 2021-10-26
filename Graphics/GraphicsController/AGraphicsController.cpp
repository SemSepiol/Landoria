#include "AGraphicsController.h"
#include <iostream>
#include <random>

AGraphicsController::AGraphicsController(class IGameForGraphic* _game_controller)
  :game_controller{_game_controller}, game_window{new GameWindow(this)}, upper_menu{new class UpperMenu(this)},
    bottom_menu{new class BottomMenu(this)}, _map{new Map(this)}, calc{new Calculations{}}
{}

void AGraphicsController::start()
{
  game_window->show();
}

QWidget* AGraphicsController::window() const
{
  return game_window.get();
}

Calculations* AGraphicsController::calculations() const
{
  return calc.get();
}

void AGraphicsController::create_elements()
{
  set_win_settings();
  create_uppermenu();
  create_bottommenu();
  create_map();
}

QPoint AGraphicsController::map_center_in_win_map()
{
  return {_map_center.x(), _map_center.y()-_size_uppermenu.height};
}

void AGraphicsController::create_uppermenu()
{
  _size_uppermenu = {_size_win.width, _size_win.height/30};
  upper_menu->set_geometry({0,0}, _size_uppermenu);
}

void AGraphicsController::create_bottommenu()
{
  _size_bottommenu = {_size_win.width, _size_win.height/30};
  QPoint pos{_size_win.width - _size_uppermenu.width, _size_win.height - _size_uppermenu.height};
  bottom_menu->set_geometry(pos, _size_uppermenu);
}

void AGraphicsController::create_map()
{
  num_cell = {game_controller->count_cell_x(), game_controller->count_cell_y()};
  calc->set_side(130);
  _size_win_map = {_size_win.width, _size_win.height - _size_uppermenu.height - _size_bottommenu.height};

  do_size_map();
  _win_map_center = {_size_win_map.width/2, _size_win_map.height/2 + _size_uppermenu.height};
  _map_center = _win_map_center;
  _map->do_cells();


  CreateMap creator_map{this};
  creator_map.create_map(_map.get());
  creator_map.add_resource(_map.get());

  //  game_window->update();
}

void AGraphicsController::set_win_settings()
{
  _size_win = {game_controller->width_win(), game_controller->height_win()};
}

size_t AGraphicsController::count_cell_x() const
{
  return num_cell.x;
}

size_t AGraphicsController::count_cell_y() const
{
  return num_cell.y;
}

Size AGraphicsController::size_win() const
{
  return _size_win;
}

Size AGraphicsController::size_win_map() const
{
  return _size_win_map;
}

Size AGraphicsController::size_map() const
{
  return _size_map;
}

QPoint AGraphicsController::win_map_center() const
{
  return _win_map_center;
}

QPoint AGraphicsController::map_center() const
{
  return _map_center;
}

void AGraphicsController::draw_elements()
{
  _map->draw(_map_center);
}

void AGraphicsController::move_map(QPoint move_point)
{
  //  QPoint new_map_center = map_center + move_point;
  if(!enabled_map)
    return;
  _map_center += move_point;
  control_pos_map();
  game_window->update();
}

void AGraphicsController::resize_map(double coeff, QPoint pos_mouse)
{
  if(6*calc->hexagon_side() * coeff > _size_win.height)
    return;

  int old_side = calc->hexagon_side();
  QPoint old_map_center = _map_center;
  int old_hexagon_height = calc->hexagon_height();

  calc->set_side(calc->my_round(coeff * calc->hexagon_side()));
  do_size_map();

  QPoint point1 = pos_mouse - _map_center;
  QPoint point2 = {(pos_mouse.x() - _map_center.x()) * old_hexagon_height / calc->hexagon_height(),
                   int((pos_mouse.y() - _map_center.y())/coeff)};
  _map_center += (point2 - point1);

  if((_size_map.height < _size_win_map.height) || ( _size_map.width < _size_win_map.width))
  {
    calc->set_side(old_side);
    do_size_map();
    _map_center = old_map_center;
  }
  else
    control_pos_map();

  game_window->update();
}

int AGraphicsController::map_upper_edge() const
{
  return _size_uppermenu.height;
}

int AGraphicsController::map_bottom_edge() const
{
  return _size_win.height - _size_bottommenu.height;
}

void AGraphicsController::exit()
{
  game_window->hide();
  game_controller->exit();
}

void AGraphicsController::control_pos_map()
{
  if (_map_center.y() - _win_map_center.y() + _size_win_map.height/2 > _size_map.height/2)
    _map_center.setY(_win_map_center.y() - _size_win_map.height/2 + _size_map.height/2);
  else if (_win_map_center.y() - _map_center.y() + _size_win_map.height/2 > _size_map.height/2)
    _map_center.setY(_win_map_center.y() + _size_win_map.height/2 - _size_map.height/2);

  if (_map_center.x() - _win_map_center.x() + _size_win_map.width/2 > _size_map.width/2)
    _map_center.setX(_win_map_center.x() - _size_win_map.width/2 + _size_map.width/2);
  else if (_win_map_center.x() - _map_center.x() + _size_win_map.width/2 > _size_map.width/2)
    _map_center.setX(_win_map_center.x() + _size_win_map.width/2 - _size_map.width/2);
}

void AGraphicsController::do_size_map()
{
  _size_map.height = calc->hexagon_side()*int(num_cell.y) + calc->hexagon_side()*(int(num_cell.y)+1)/2;
  _size_map.width = calc->hexagon_height()*(int(num_cell.x)*2+1);
}
