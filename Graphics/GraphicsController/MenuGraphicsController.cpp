#include "MenuGraphicsController.h"
#include <iostream>

MenuGraphicsController::MenuGraphicsController(IGraphicsController* _graphics_controller)
  :graphics_controller{_graphics_controller}
{}

QWidget* MenuGraphicsController::window() const
{
  return graphics_controller->get_game_window();
}

void MenuGraphicsController::move_map(QPoint move_point)
{
  auto map_gc = graphics_controller->get_imap_gc_full();
  map_gc->move_map(move_point);
}

void MenuGraphicsController::exit()
{
  graphics_controller->get_game_window()->hide();
  graphics_controller->get_game_controller()->exit();
}

void MenuGraphicsController::show_minimap()
{
  auto minimap = graphics_controller->get_imap_gc_full()->get_minimap();
  if(minimap->isVisible())
    minimap->hide();
  else
    minimap->show();
  event_open_menu_type_map();
}

void MenuGraphicsController::next_move()
{
  graphics_controller->get_game_controller()->next_move();
}

void MenuGraphicsController::menu_unit_event(class Unit* unit, Event* event)
{
  auto iwindow_gc = graphics_controller->get_iwindow_gc_full();
  if(event->event == Events::Move)
  {
    if(graphics_controller->get_is_moving_unit())
      iwindow_gc->stop_check_move_unit();
    else
      iwindow_gc->start_check_move_unit(unit);
    return;
  }

  if(event->event == Events::Build)
  {
    BuildEvent* build_event = static_cast<BuildEvent*>(event);
    build_event->pos_cell = graphics_controller->get_pos_tracking_unit();
  }

  graphics_controller->get_game_controller()->current_player()->menu_event(unit, event);

  auto imenu_gc = graphics_controller->get_imenu_gc_full();
  imenu_gc->del_menu_unit();
  //  no_highlight_unit(unit)
}

void MenuGraphicsController::delete_townmenu()
{
  graphics_controller->set_town_menu(nullptr);
  upper_menu->set_enable_move_map(true);
  bottom_menu->show();

  graphics_controller->get_game_controller()->current_player()->del_menu_town();

  graphics_controller->get_enabled_map() = true;
}

void MenuGraphicsController::do_inform_widget(std::vector<std::pair<QString, QColor>> text)
{
  graphics_controller->get_game_window()->do_inform_widget(text);
}

void MenuGraphicsController::del_inform_widget()
{
  graphics_controller->get_game_window()->del_inform_widget();
}

void MenuGraphicsController::open_menu_lists()
{
  menu_lists->show();
}

void MenuGraphicsController::close_menu_lists()
{
  menu_lists->hide();
}

void MenuGraphicsController::open_menu_science()
{
  menu_lists->hide();
  wid_open_menu_lists->switch_arrow();

  menu_science.reset(new MenuScience(this, player_science()));
  Size size = graphics_controller->get_size_win();
  QPoint pos = {0,0};
  menu_science->set_geometry(pos, size);
  menu_science->hide();
  menu_science->show();
}

void MenuGraphicsController::close_menu_science()
{
  menu_science.reset();
}

void MenuGraphicsController::event_open_menu_type_map()
{
  if(menu_type_map)
  {
    close_menu_type_map();
    open_menu_type_map();
  }
}

void MenuGraphicsController::click_open_menu_type_map()
{
  if(menu_type_map)
    close_menu_type_map();
  else
    open_menu_type_map();
}

void MenuGraphicsController::open_menu_type_map()
{
  menu_type_map.reset(new MenuTypeMap(this, map()));
  QPoint pos;
  Size size_win = graphics_controller->get_size_win();
  Size size{size_win.width/10, size_win.height/5};
  if(graphics_controller->get_imap_gc_full()->get_minimap()->is_enable())
  {
    Calculations calc{graphics_controller->get_hexagon_side_minimap()};
    int num_cell_x = int(graphics_controller->get_num_cell().x);
    int width_minimap = calc.hexagon_height()*(num_cell_x*2+1);

    pos = {size_win.width - size.width - width_minimap,
           size_win.height - graphics_controller->get_size_bottommenu().height - size.height};
  }
  else{
    pos = bottom_menu->open_type_map_butt().topRight() -
        QPoint{size.width, -size_win.height + size.height + graphics_controller->get_size_bottommenu().height};
  }

  menu_type_map->set_geometry(pos, size);
  menu_type_map->hide();
  menu_type_map->show();
}

void MenuGraphicsController::close_menu_type_map()
{
  menu_type_map.reset();
}

void MenuGraphicsController::set_type_map(TypeMap type_map)
{
  map()->set_type_map(type_map);
}

PlayerScience* MenuGraphicsController::player_science()
{
  return graphics_controller->get_game_controller()->current_player()->player_science();
}

void MenuGraphicsController::create_elements()
{
  create_bottommenu();
  create_uppermenu();
  create_menu_lists();
}

void MenuGraphicsController::create_uppermenu()
{
  upper_menu.reset(new class UpperMenu(this));
  Size size_win = graphics_controller->get_size_win();
  Size& size_uppermenu = graphics_controller->get_size_uppermenu();

  size_uppermenu = {size_win.width, size_win.height/30};
  upper_menu->set_geometry({0,0}, size_uppermenu);
  upper_menu->hide();
  upper_menu->show();
}

void MenuGraphicsController::create_bottommenu()
{
  bottom_menu.reset(new class BottomMenu(this));
  Size size_win = graphics_controller->get_size_win();
  Size& size_bottommenu = graphics_controller->get_size_bottommenu();
  size_bottommenu = {size_win.width, size_win.height/30};
  QPoint pos{size_win.width - size_bottommenu.width, size_win.height - size_bottommenu.height};
  bottom_menu->set_geometry(pos, size_bottommenu);
  bottom_menu->hide();
  bottom_menu->show();
}

void MenuGraphicsController::create_menu_lists()
{
  wid_open_menu_lists.reset(new OpenMenuLists(this));
  menu_lists.reset(new MenuLists(this));

  Size size_win = graphics_controller->get_size_win();
  size_open_menu_lists = {size_win.height/30, size_win.height/30};
  QPoint pos{0, graphics_controller->get_size_uppermenu().height};
  wid_open_menu_lists->set_geometry(pos, size_open_menu_lists);
  wid_open_menu_lists->hide();
  wid_open_menu_lists->show();

  size_menu_lists = {size_win.height/10, size_win.height/10};
  pos += {0, size_open_menu_lists.height};
  menu_lists->set_geometry(pos, size_menu_lists);
  menu_lists->hide();
}

void MenuGraphicsController::del_menu_unit()
{
  graphics_controller->set_unit_menu(nullptr);
  graphics_controller->set_unit_information(nullptr);

  bool& is_tracking_unit = graphics_controller->get_iplayer_gc()->get_is_tracking_unit();
  Position pos_tracking_unit = graphics_controller->get_pos_tracking_unit();
  class Unit* tracking_unit = graphics_controller->get_tracking_unit();

  auto map_gc = graphics_controller->get_imap_gc_full();
  map_gc->no_highlight_unit(tracking_unit, pos_tracking_unit);
  is_tracking_unit = false;
  tracking_unit = nullptr;
}

void MenuGraphicsController::press_escape()
{
  if(menu_science)
    close_menu_science();
  if(graphics_controller->get_town_menu())
    delete_townmenu();
}

UpperMenu* MenuGraphicsController::get_upper_menu()
{
  return upper_menu.get();
}

BottomMenu* MenuGraphicsController::get_bottom_menu()
{
  return bottom_menu.get();
}

Map* MenuGraphicsController::map()
{
  return graphics_controller->get_imap_gc_full()->get_map();
}
