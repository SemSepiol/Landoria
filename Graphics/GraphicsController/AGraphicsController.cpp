#include "AGraphicsController.h"
#include <iostream>
#include <random>

AGraphicsController::AGraphicsController(class IGameForGraphic* _game_controller)
  :game_controller{_game_controller}, game_window{new GameWindow(this)}, upper_menu{new class UpperMenu(this)},
    bottom_menu{new class BottomMenu(this)}, map{new Map(this)}, calc{new Calculations{}}
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
  return {map_center.x(), map_center.y()-_height_uppermenu};
}

void AGraphicsController::create_uppermenu()
{
  _height_uppermenu = _height_win/30;
  _width_uppermenu = _width_win;
  upper_menu->set_geometry({0,0}, _width_uppermenu, _height_uppermenu);
}

void AGraphicsController::create_bottommenu()
{

  _height_bottommenu = _height_win/30;
  _width_bottommenu = _width_win;
  QPoint pos{_width_win - _width_uppermenu, _height_win - _height_uppermenu};
  bottom_menu->set_geometry(pos, _width_uppermenu, _height_uppermenu);
}

void AGraphicsController::create_map()
{
  num_cell_x = game_controller->count_cell_x();
  num_cell_y = game_controller->count_cell_y();
  calc->set_side(130);
  _height_win_map = _height_win - _height_uppermenu - _height_bottommenu;
  _width_win_map = _width_win;

  do_size_map();
  _win_map_center = {_width_win_map/2, _height_win_map/2 + _height_uppermenu};
  map_center = _win_map_center;
  map->do_cells();

  CreateMap creator_map{this};
  creator_map.create_map(map.get());
  creator_map.add_resource(map.get());

  //  game_window->update();
}

void AGraphicsController::set_win_settings()
{
  _height_win = game_controller->height_win();
  _width_win = game_controller->width_win();
  //  std::cout << _height_win << " " << _width_win << std::endl;
}

int AGraphicsController::count_cell_x() const
{
  return num_cell_x;
}

int AGraphicsController::count_cell_y() const
{
  return num_cell_y;
}

int AGraphicsController::width_win() const
{
  return _width_win;
}

int AGraphicsController::height_win() const
{
  return _height_win;
}

int AGraphicsController::width_win_map() const
{
  return _width_win_map;
}

int AGraphicsController::height_win_map() const
{
  return _height_win_map;
}

int AGraphicsController::width_map() const
{
  return _width_map;
}

int AGraphicsController::height_map() const
{
  return _height_map;
}

QPoint AGraphicsController::win_map_center() const
{
  return _win_map_center;
}

void AGraphicsController::draw_map()
{
  map->draw(map_center);
}

void AGraphicsController::move_map(QPoint move_point)
{
  //  QPoint new_map_center = map_center + move_point;
  map_center += move_point;
  control_pos_map();
  game_window->update();
}

void AGraphicsController::resize_map(double coefficient)
{
  if(6*calc->hexagon_side() * coefficient > _height_win)
    return;

  int old_side = calc->hexagon_side();

  calc->set_side(calc->my_round(coefficient * calc->hexagon_side()));
  do_size_map();

  if((_height_map < _height_win_map) || ( _width_map < _width_win_map))
  {
    calc->set_side(old_side);
    do_size_map();
  }
  else
    control_pos_map();

  game_window->update();
}

void AGraphicsController::exit()
{
  game_window->hide();
  game_controller->exit();
}

void AGraphicsController::control_pos_map()
{
  if (map_center.y() - _win_map_center.y() + _height_win_map/2 > _height_map/2)
    map_center.setY(_win_map_center.y() - _height_win_map/2 + _height_map/2);
  else if (_win_map_center.y() - map_center.y() + _height_win_map/2 > _height_map/2)
    map_center.setY(_win_map_center.y() + _height_win_map/2 - _height_map/2);

  if (map_center.x() - _win_map_center.x() + _width_win_map/2 > _width_map/2)
    map_center.setX(_win_map_center.x() - _width_win_map/2 + _width_map/2);
  else if (_win_map_center.x() - map_center.x() + _width_win_map/2 > _width_map/2)
    map_center.setX(_win_map_center.x() + _width_win_map/2 - _width_map/2);
}

void AGraphicsController::do_size_map()
{
  _height_map = calc->hexagon_side()*num_cell_y + calc->hexagon_side()*(num_cell_y+1)/2;
  _width_map = calc->hexagon_height()*(num_cell_x*2+1);
}
