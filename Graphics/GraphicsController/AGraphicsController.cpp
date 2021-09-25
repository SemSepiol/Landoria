#include "AGraphicsController.h"
#include <iostream>
#include <random>

AGraphicsController::AGraphicsController(class IGameForGraphic* _game_controller)
  :game_controller{_game_controller}, game_window{new GameWindow(this)}, upper_menu{new class UpperMenu(this)},
    map{new Map(this)}, calc{new Calculations{}}
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
  create_map();
}

void AGraphicsController::create_uppermenu()
{
  _height_menu = 50;
  _width_menu = _width_win;
  upper_menu->set_size();
}

void AGraphicsController::create_map()
{
  num_cell_x = game_controller->count_cell_x();
  num_cell_y = game_controller->count_cell_y();
  calc->set_side(130);
  _height_win_map = _height_win - _height_menu;
  _width_win_map = _width_win;

  do_size_map();
  _win_map_center = {_width_win/2, _height_win/2 + _height_menu};
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
  QPoint new_map_center = map_center + move_point;
  if (abs(new_map_center.y() - _win_map_center.y()) + _height_win_map/2 > _height_map/2)
    move_point.setY(0);
  if (abs(new_map_center.x() - _win_map_center.x()) + _width_win_map/2 > _width_map/2)
    move_point.setX(0);
  map_center += move_point;
  game_window->update();
}

void AGraphicsController::resize_map(double coefficient)
{
  int old_side = calc->hexagon_side();

  calc->set_side(calc->my_round(coefficient * calc->hexagon_side()));
  do_size_map();

  if((_height_map < _height_win_map) ||( _width_map < _width_win_map))
  {
    calc->set_side(old_side);
    do_size_map();
  }
  else
  {
    if (abs(map_center.x() - _win_map_center.x()) + _width_win_map/2 > _width_map/2)
    {
      QPoint move = QPoint{abs(map_center.x() - _win_map_center.x()) + _width_win_map/2 - _width_map/2,0};
      if (map_center.x() - _win_map_center.x() < 0)
        map_center += move;
      else
        map_center -= move;
    }

    if (abs(map_center.x() - _win_map_center.x()) + _width_win_map/2 > _width_map/2)
    {
      QPoint move = QPoint{abs(map_center.x() - _win_map_center.x()) + _width_win_map/2 - _width_map/2,0};
      if (map_center.x() - _win_map_center.x() < 0)
        map_center += move;
      else
        map_center -= move;
    }

    if (abs(map_center.y() - _win_map_center.y()) + _height_win_map/2 > _height_map/2)
    {
      QPoint move = QPoint{0, abs(map_center.y() - _win_map_center.y()) + _height_win_map/2 - _height_map/2};
      if (map_center.y() - _win_map_center.y() < 0)
        map_center += move;
      else
        map_center -= move;
    }
  }

  game_window->update();
}

void AGraphicsController::resize_win(const QSize& new_size)
{
//  resize_map(std::max(new_size.width()*1. / _width_win, new_size.height()*1. / _height_win));

  _width_win = new_size.width();
  _height_win = new_size.height();
  game_window->update();
}

//void AGraphicsController::click(QPoint pos)
//{
////  std::cout << (pos - map_center).x() << " " << (pos - map_center).y() << std::endl;
////  std::cout << "=====" << std::endl;
//  auto pair = map->click(pos - map_center);
//  Cell* cell = pair.first;
//  IContent* content = pair.second;

////  if (!cell)
////    std::cout << "No cell" << std::endl;
////  if (content)
////    std::cout << content->what_content_I() << std::endl;
////  else
////    std::cout << "No content" << std::endl;
//}

int AGraphicsController::width_menu() const
{
  return _width_menu;
}

int AGraphicsController::height_menu() const
{
  return _height_menu;
}

QPoint AGraphicsController::uppermenu_top_left() const
{
  return _uppermenu_top_left;
}

void AGraphicsController::exit()
{
//  std::cout << "exit" << std::endl;
  game_window->hide();
  game_controller->exit();
}

void AGraphicsController::do_size_map()
{
  _height_map = calc->hexagon_side()*num_cell_y + calc->hexagon_side()*(num_cell_y+1)/2;
  _width_map = calc->hexagon_height()*(num_cell_x*2+1);
}

void AGraphicsController::do_contents()
{
  for(int i{0}; i < num_cell_x; ++i)
    for(int j{0}; j < num_cell_y; ++j)
    {
      ControlContents controlcontents{map->cell_by_index(size_t(i), size_t(j))};
//      controlcontents.add_unit(Units::Worker);
//      controlcontents.add_unit(Units::Citizen);
//      controlcontents.add_unit(Units::Swordsman);
//      controlcontents.add_unit(Units::Bowman);
//      controlcontents.add_building(Buildings(rand() % 10));
    }
//  ControlContents controlcontents{map->cell_by_index(num_cell_x/2-1, num_cell_y/2)};
//  controlcontents.add_unit(Units::Worker);
//  controlcontents.add_unit(Units::Worker);
//  controlcontents.add_unit(Units::Worker);
//  controlcontents.add_unit(Units::Worker);
}


