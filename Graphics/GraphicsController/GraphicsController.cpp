#include "GraphicsController.h"
#include <iostream>
#include <random>

GraphicsController::GraphicsController(class IGameForGraphic* _game_controller)
  :game_controller{_game_controller}, window_gc{new WindowGraphicsController(this)},
    map_gc{new MapGraphicsController(this)},
    player_gc{new PlayerGraphicsController(this)},
    menu_gc{new MenuGraphicsController(this)},
    menu_start_gc{new MenuStartGraphicsController(this)}
{}

void GraphicsController::start_game()
{
  game_controller->start_game();
}

void GraphicsController::do_start_menu()
{
  window_gc->do_window();
  window_gc->get_window()->show();
  window_gc->set_win_settings();
  menu_start_gc->do_start_menu();
}

QWidget* GraphicsController::window() const
{
  return window_gc->get_window();
}

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

void GraphicsController::create_elements()
{
  menu_gc->create_elements();
  map_gc->create_map();


  side_square_unit_menu = _size_win.width/20;
  map_gc->create_minimap();
  window_gc->get_window()->update();
}

Size& GraphicsController::get_size_win()
{
  return _size_win;
}

Size& GraphicsController::get_size_uppermenu()
{
  return _size_uppermenu;
}

Size& GraphicsController::get_size_bottommenu()
{
  return _size_bottommenu;
}

Size& GraphicsController::get_size_win_map()
{
  return _size_win_map;
}

Size& GraphicsController::get_size_map()
{
  return _size_map;
}

Position& GraphicsController::get_num_cell()
{
  return num_cell;
}

QPoint& GraphicsController::get_map_center()
{
  return _map_center;
}

QPoint& GraphicsController::get_win_map_center()
{
  return _win_map_center;
}

bool& GraphicsController::get_enabled_map()
{
  return enabled_map;
}

IGameForGraphic* GraphicsController::get_game_controller()
{
  return game_controller;
}

GameWindow* GraphicsController::get_game_window()
{
  return window_gc->get_window();
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

void GraphicsController::set_drawway(DrawWay* _drawway)
{
  drawway.reset(_drawway);
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
StartMoveInform* GraphicsController::get_start_move_inform()
{
  return start_move_inform.get();
}

IWindowGraphicsControllerFull* GraphicsController::get_iwindow_gc_full()
{
  return window_gc.get();
}

IMenuGraphicsControllerFull* GraphicsController::get_imenu_gc_full()
{
  return menu_gc.get();
}

IPlayerGraphicsControllerFull* GraphicsController::get_iplayer_gc()
{
  return player_gc.get();
}

IMapGraphicsControllerFull* GraphicsController::get_imap_gc_full()
{
  return map_gc.get();
}

IMenuStartGraphicsController* GraphicsController::get_imenu_start_full()
{
  return menu_start_gc.get();
}
