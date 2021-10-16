#include "GraphicsController.h"
#include <iostream>

#include "windows.h"


GraphicsController::GraphicsController(IGameForGraphic* _game_controller)
  : AGraphicsController{_game_controller}, minimap{new Minimap{game_window.get(), _map.get(), this}}
{}

void GraphicsController::create_elements()
{
  AGraphicsController::create_elements();
  side_square_unit_menu = _size_win.width/20;
  create_minimap();
}

void GraphicsController::do_menu_unit(PlayerUnit* unit)
{
  is_tracking_unit = true;
  tracking_unit = unit->unit;
  pos_tracking_unit = unit->pos;

  Cell* cell = _map->cell_by_indexes(unit->pos);
  unit_menu.reset(FactoryMenusUnit().create_menu(game_window.get(), this, unit, cell));
  unit_menu->set_geometry(
        {0, _size_win.height - side_square_unit_menu * (unit_menu->count_button()+1) - _size_bottommenu.height},
        side_square_unit_menu);

  unit_menu->hide();
  unit_menu->show();

  unit_information.reset(new UnitInformation(game_window.get(), unit->unit));
  unit_information->set_geometry({0, _size_win.height - _size_bottommenu.height - side_square_unit_menu},
                                 side_square_unit_menu);
  unit_information->hide();
  unit_information->show();
}

void GraphicsController::do_menu_town(PlayerTown* town)
{
  town_menu.reset(new MenuTown{this, town});
  town_menu->set_geometry({0, _size_uppermenu.height},
                          {_size_win.width, _size_win.height-_size_uppermenu.height});
  town_menu->start();
  upper_menu->set_enable_move_map(false);
}

void GraphicsController::centering_by_cell(Position pos_cell)
{
  QPoint point = _map->point_of_cell_in_win(pos_cell);
  move_map(_win_map_center - point);
}

void GraphicsController::highlight_unit(class Unit* unit, Position pos_cell)
{

  ControlContents controlcontents{_map->cell_by_indexes(pos_cell)};
  controlcontents.set_highlight_unit(unit, true);
}

void GraphicsController::draw_playermap(PlayerMap* playermap)
{
  for(size_t i{0}; i < num_cell.x; ++i)
    for(size_t j{0}; j < num_cell.y; ++j)
    {
      ControlContents controcontents{_map->cell_by_indexes({i,j})};
      controcontents.set_show_cell(playermap->get_show_cell({i,j}));
    }
}

Map* GraphicsController::mapforfind() const
{
  return _map.get();
}

void GraphicsController::no_highlight_unit(class Unit* unit, Position pos_cell)
{
  ControlContents controlcontents{_map->cell_by_indexes(pos_cell)};
  controlcontents.set_highlight_unit(unit, false);
}

void GraphicsController::move_unit(class Unit* unit, Position old_position, Position new_position)
{
  ControlContents controlcontents_old{_map->cell_by_indexes({old_position})};
  ControlContents controlcontents_new{_map->cell_by_indexes({new_position})};

  controlcontents_old.pop_content(unit);
  controlcontents_new.add_unit(unit);
  game_window->update();
}

class Building* GraphicsController::build(Buildings type_building, Position pos_cell)
{
  ControlContents controlcontents{_map->cell_by_indexes(pos_cell)};
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

  auto pair = _map->click(mouse_pos - _map_center);
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
    auto pair = _map->click(new_pos - _map_center);
    Cell* cell = pair.first;
    if(!cell)
    {
      return;
    }
    Position end_way = _map->indexes_by_cell(pair.first);
    if(drawway)
      drawway->set_end_way(end_way);
    game_window->update();
  }
}

void GraphicsController::click(QPoint pos)
{
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

class Unit* GraphicsController::add_unit(Units type_unit, Position pos_cell)
{
  ControlContents controlcontents{_map->cell_by_indexes(pos_cell)};
  class Unit* unit = static_cast<class Unit*>(controlcontents.add_unit(type_unit));
  return unit;
}

void GraphicsController::del_unit(class Unit* unit, Position pos_cell)
{
  ControlContents controlcontents{_map->cell_by_indexes(pos_cell)};
  controlcontents.del_content(unit);
}

void GraphicsController::del_build(Position pos_cell)
{
  ControlContents controlcontents{_map->cell_by_indexes(pos_cell)};
  controlcontents.del_building();
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

void GraphicsController::resize_map(double coefficient, QPoint pos_mouse)
{
  AGraphicsController::resize_map(coefficient, pos_mouse);
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
//  no_highlight_unit(unit)
}

void GraphicsController::delete_townmenu()
{
  town_menu.reset();
  upper_menu->set_enable_move_map(true);
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

