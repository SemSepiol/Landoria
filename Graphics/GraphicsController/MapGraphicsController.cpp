#include "MapGraphicsController.h"

MapGraphicsController::MapGraphicsController(IGraphicsController* _graphics_controller)
  :graphics_controller{_graphics_controller}
{}

QWidget* MapGraphicsController::window() const
{
  return graphics_controller->get_game_window();
}

Calculations* MapGraphicsController::calculations() const
{
  return graphics_controller->get_calc();
}

size_t MapGraphicsController::count_cell_x() const
{
  return graphics_controller->get_num_cell().x;
}

size_t MapGraphicsController::count_cell_y() const
{
  return graphics_controller->get_num_cell().y;
}

Size MapGraphicsController::size_map() const
{
  return graphics_controller->get_size_map();
}

Size MapGraphicsController::size_win_map() const
{
  return graphics_controller->get_size_win_map();
}

QPoint MapGraphicsController::win_map_center() const
{
  return graphics_controller->get_win_map_center();
}

QPoint MapGraphicsController::map_center() const
{
  return graphics_controller->get_map_center();
}

void MapGraphicsController::move_map(double coeffx, double coeffy)
{
  if(!graphics_controller->get_enabled_map())
    return;

  Size size_map = _size_map();
  _map_center().setX(int(size_map.width * coeffx));
  _map_center().setY(int(size_map.height * coeffy));
  control_pos_map();
  set_win_rect_minimap();
  graphics_controller->get_game_window()->update();
}

QPoint MapGraphicsController::map_center_in_win_map()
{
  Size size_uppermenu = graphics_controller->get_size_uppermenu();
  return {_map_center().x(), _map_center().y() - size_uppermenu.height};
}

void MapGraphicsController::control_pos_map()
{
  if (_map_center().y() - _win_map_center().y() + size_win_map().height/2 > size_map().height/2)
    _map_center().setY(_win_map_center().y() - size_win_map().height/2 + size_map().height/2);
  else if (_win_map_center().y() - _map_center().y() + size_win_map().height/2 > size_map().height/2)
    _map_center().setY(_win_map_center().y() + size_win_map().height/2 - size_map().height/2);

  if (_map_center().x() - _win_map_center().x() + size_win_map().width/2 > size_map().width/2)
    _map_center().setX(_win_map_center().x() - size_win_map().width/2 + size_map().width/2);
  else if (_win_map_center().x() - _map_center().x() + size_win_map().width/2 > size_map().width/2)
    _map_center().setX(_win_map_center().x() + size_win_map().width/2 - size_map().width/2);
}

void MapGraphicsController::set_win_rect_minimap()
{
  double coeffx = map_center_in_win_map().x()*1. / size_map().width;
  double coeffy = map_center_in_win_map().y()*1. / size_map().height;
  double coeff_width = size_win_map().width*1. / size_map().width;
  double coeff_height = size_win_map().height*1. / size_map().height;
  minimap()->set_win_rect(coeffx, coeffy, coeff_width, coeff_height);
}

void MapGraphicsController::move_map(QPoint move_point)
{
  //  QPoint new_map_center = map_center + move_point;
  if(!graphics_controller->get_enabled_map())
    return;
  _map_center() += move_point;
  control_pos_map();
  graphics_controller->get_game_window()->update();

  set_win_rect_minimap();
}

void MapGraphicsController::resize_map(double coeff, QPoint pos_mouse)
{
  if(!graphics_controller->get_enabled_map())
    return;

  if(6*calculations()->hexagon_side() * coeff > graphics_controller->get_size_win().height)
    return;

  int old_side = calculations()->hexagon_side();
  QPoint old_map_center = _map_center();
  int old_hexagon_height = calculations()->hexagon_height();

  calculations()->set_side(calculations()->my_round(coeff * calculations()->hexagon_side()));
  do_size_map();

  QPoint point1 = pos_mouse - _map_center();
  QPoint point2 = {(pos_mouse.x() - _map_center().x()) * old_hexagon_height / calculations()->hexagon_height(),
                   int((pos_mouse.y() - _map_center().y())/coeff)};
  _map_center() += (point2 - point1);

  if((size_map().height < size_win_map().height) || (size_map().width < size_win_map().width))
  {
    calculations()->set_side(old_side);
    do_size_map();
    _map_center() = old_map_center;
  }
  else
    control_pos_map();

  set_win_rect_minimap();
  graphics_controller->get_game_window()->update();
}

void MapGraphicsController::do_size_map()
{
  _size_map().height = calculations()->hexagon_side()*int(count_cell_y()) + calculations()->hexagon_side()*(int(count_cell_y())+1)/2;
  _size_map().width = calculations()->hexagon_height()*(int(count_cell_x())*2+1);
}

void MapGraphicsController::create_map()
{
  auto game_controller = graphics_controller->get_game_controller();
  graphics_controller->get_num_cell() = {game_controller->count_cell_x(), game_controller->count_cell_y()};
  calculations()->set_side(130);

  int height_uppermenu = graphics_controller->get_size_uppermenu().height;
  int height_bottommenu = graphics_controller->get_size_bottommenu().height;
  _size_win_map() = {size_win().width, size_win().height - height_uppermenu - height_bottommenu};

  do_size_map();
  _win_map_center() = {_size_win_map().width/2, _size_win_map().height/2 + height_uppermenu};
  _map_center() = _win_map_center();
  map()->do_cells();


  CreateMap creator_map{this};
  creator_map.create_map(map());
  creator_map.add_resource(map());

  //  game_window->update();
}

void MapGraphicsController::create_minimap()
{
  Size size_win = graphics_controller->get_size_win();

  int width_minimap = size_win.width/3;
  int height_minimap = size_win.height/3;

  int hexagon_height1 = width_minimap/(int(count_cell_x())*2+1);
  int side1 = calculations()->my_round(hexagon_height1*2/sqrt(3));

  int side2 = height_minimap*2 / (3*int(count_cell_y())+1);

  int& hexagon_side_minimap = graphics_controller->get_hexagon_side_minimap();

  hexagon_side_minimap = std::min(side1, side2);

  int height_bottommenu = graphics_controller->get_size_bottommenu().height;
  minimap()->set_geometry(QPoint{size_win.width, size_win.height - height_bottommenu}, hexagon_side_minimap);
  set_win_rect_minimap();
  minimap()->hide();
}

void MapGraphicsController::no_highlight_unit(class Unit* unit, Position pos_cell)
{
  ControlContents controlcontents{map()->cell_by_indexes(pos_cell)};
  controlcontents.set_highlight_unit(unit, false);
}

Size MapGraphicsController::size_win() const
{
  return graphics_controller->get_size_win();
}

Map* MapGraphicsController::map()
{
  return graphics_controller->get_map();
}

Minimap* MapGraphicsController::minimap()
{
  return graphics_controller->get_minimap();
}

Size& MapGraphicsController::_size_map()
{
  return graphics_controller->get_size_map();
}

Size& MapGraphicsController::_size_win_map()
{
  return graphics_controller->get_size_win_map();
}

QPoint& MapGraphicsController::_win_map_center()
{
  return graphics_controller->get_win_map_center();
}

QPoint& MapGraphicsController::_map_center()
{
  return graphics_controller->get_map_center();
}
