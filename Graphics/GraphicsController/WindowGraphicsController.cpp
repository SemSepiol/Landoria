#include "WindowGraphicsController.h"

WindowGraphicsController::WindowGraphicsController(IGraphicsController* _graphics_controller)
  :graphics_controller{_graphics_controller}
{}

Size WindowGraphicsController::size_win() const
{
  return graphics_controller->get_size_win();
}

void WindowGraphicsController::draw_elements()
{
  if(!map())
    return;

  map()->draw(graphics_controller->get_map_center());
  if(drawway())
    drawway()->draw();
}

void WindowGraphicsController::move_map(QPoint move_point)
{
  auto map_gc = graphics_controller->get_imap_gc_full();
  map_gc->move_map(move_point);
}

void WindowGraphicsController::resize_map(double coeff, QPoint pos_mouse)
{
  auto map_gc = graphics_controller->get_imap_gc_full();
  map_gc->resize_map(coeff, pos_mouse);
}

void WindowGraphicsController::click(QPoint pos)
{
  if(!graphics_controller->get_enabled_map())
    return;

  auto pair = map()->click(pos - graphics_controller->get_map_center());
  Cell* cell = pair.first;
  IContent* content = pair.second;


  if(graphics_controller->get_is_moving_unit())
  {
    unit_moved_to_cell(cell);
    return;
  }

  auto imenu_gc = graphics_controller->get_imenu_gc_full();
  imenu_gc->del_menu_unit();
  if(content)
  {
    if (content->what_content_I() == Contents::Unit)
      game_controller()->current_player()->click_unit(static_cast<class Unit*>(content));
    else if (content->what_content_I() == Contents::Building)
    {
      class Building* building = static_cast<class Building*>(content);
      if(building->what_building_I() == Buildings::Town)
        game_controller()->current_player()->click_town(static_cast<class Town*>(building));
    }
  }
  game_window->update();
}

void WindowGraphicsController::start_check_move_unit()
{
  if(graphics_controller->get_tracking_unit())
    start_check_move_unit(graphics_controller->get_tracking_unit());
}

void WindowGraphicsController::stop_check_move_unit(QPoint mouse_pos)
{
  if(!graphics_controller->get_tracking_unit())
    return;

  auto pair = map()->click(mouse_pos - graphics_controller->get_map_center());
  Cell* cell = pair.first;
  if(cell)
    unit_moved_to_cell(cell);
  else
    stop_check_move_unit();
}

void WindowGraphicsController::move_mouse(QPoint new_pos)
{
  if(!graphics_controller->get_enabled_map())
    return;

  auto pair = map()->click(new_pos - graphics_controller->get_map_center());
  Cell* cell = pair.first;
  if(!cell)
    return;
  graphics_controller->get_imenu_gc_full()->get_bottom_menu()->update_infofm(cell);

  if(graphics_controller->get_is_moving_unit())
  {
    Position end_way = map()->indexes_by_cell(pair.first);
    if(drawway())
      drawway()->set_end_way(end_way);
    game_window->update();
  }
}

void WindowGraphicsController::press_enter()
{
  if(graphics_controller->get_start_move_inform())
    game_controller()->start_move();
}

void WindowGraphicsController::press_escape()
{
  if(graphics_controller->get_start_move_inform())
    game_controller()->start_move();
  graphics_controller->get_imenu_gc_full()->press_escape();
}

int WindowGraphicsController::map_upper_edge() const
{
  return graphics_controller->get_size_uppermenu().height;
}

int WindowGraphicsController::map_bottom_edge() const
{
  return size_win().height - graphics_controller->get_size_bottommenu().height;
}

void WindowGraphicsController::start_check_move_unit(class Unit* unit)
{
  graphics_controller->get_is_moving_unit() = true;

  Position pos_tracking_unit = graphics_controller->get_pos_tracking_unit();
  DrawWay* new_drawWay = new DrawWay{game_window.get(), map(), pos_tracking_unit, unit};
  graphics_controller->set_drawway(new_drawWay);
}

void WindowGraphicsController::stop_check_move_unit()
{
  graphics_controller->set_drawway(nullptr);
  graphics_controller->get_is_moving_unit() = false;
  game_window->update();
}

void WindowGraphicsController::set_win_settings()
{
  _size_win() = {game_controller()->width_win(), game_controller()->height_win()};
}

void WindowGraphicsController::unit_moved_to_cell(Cell* cell)
{
  Position pos_cell = map()->indexes_by_cell(cell);
  if(!graphics_controller->get_tracking_unit())
    throw std::runtime_error("click: unit_what_moving not set");
  FindUnitWay().get_way(graphics_controller->get_tracking_unit(), map(),
                        graphics_controller->get_pos_tracking_unit(), pos_cell);

  MoveEvent* move_event = new MoveEvent{pos_cell};
  game_controller()->current_player()->menu_event(graphics_controller->get_tracking_unit(), move_event);
  stop_check_move_unit();

  auto imenu_gc = graphics_controller->get_imenu_gc_full();
  imenu_gc->del_menu_unit();
}

Size& WindowGraphicsController::_size_win()
{
  return graphics_controller->get_size_win();
}

IGameForGraphic* WindowGraphicsController::game_controller() const
{
  return graphics_controller->get_game_controller();
}

DrawWay* WindowGraphicsController::drawway() const
{
  return graphics_controller->get_drawway();
}

Map* WindowGraphicsController::map()
{
  return graphics_controller->get_imap_gc_full()->get_map();
}

GameWindow* WindowGraphicsController::get_window()
{
  return game_window.get();
}

void WindowGraphicsController::do_window()
{
  game_window.reset(new GameWindow(this));
}
