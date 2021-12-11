#include "PlayerGraphicsController.h"
#include <iostream>

PlayerGraphicsController::PlayerGraphicsController(IGraphicsController* _graphics_controller)
  :graphics_controller{_graphics_controller}
{}

class Unit* PlayerGraphicsController::add_unit(Units type_unit, Position pos_cell)
{
  ControlContents controlcontents{map()->cell_by_indexes(pos_cell)};
  class Unit* unit = static_cast<class Unit*>(controlcontents.add_unit(type_unit));
  return unit;
}

void PlayerGraphicsController::move_unit(class Unit* unit, Position old_position, Position new_position)
{
  ControlContents controlcontents_old{map()->cell_by_indexes({old_position})};
  ControlContents controlcontents_new{map()->cell_by_indexes({new_position})};

  controlcontents_old.pop_content(unit);
  controlcontents_new.add_unit(unit);
  game_window()->update();
}


class Building* PlayerGraphicsController::build(Buildings type_building, Position pos_cell)
{
  ControlContents controlcontents{map()->cell_by_indexes(pos_cell)};
  if(controlcontents.has_building())
  {
    if(type_building == Buildings::Town && controlcontents.get_building()->what_building_I() != Buildings::Town)
      controlcontents.del_building();
    else
      throw std::runtime_error("build: There is already a building in this cell");
  }
  IContent* content = controlcontents.add_building(type_building);
  class Building* building = static_cast<class Building*>(content);
  game_window()->update();
  return building;
}

void PlayerGraphicsController::del_unit(class Unit* unit, Position pos_cell)
{
  ControlContents controlcontents{map()->cell_by_indexes(pos_cell)};
  controlcontents.del_content(unit);
}

void PlayerGraphicsController::del_build(Position pos_cell)
{
  ControlContents controlcontents{map()->cell_by_indexes(pos_cell)};
  controlcontents.del_building();
}

void PlayerGraphicsController::do_menu_unit(PlayerUnit* unit)
{
  is_tracking_unit = true;
  graphics_controller->get_tracking_unit() = unit->unit;
  graphics_controller->get_pos_tracking_unit() = unit->pos;

  Cell* cell = map()->cell_by_indexes(unit->pos);
  Size size_win = graphics_controller->get_size_win();
  Size size_bottommenu = graphics_controller->get_size_bottommenu();

  auto imenu_gc = graphics_controller->get_imenu_gc_full();
  graphics_controller->set_unit_menu(FactoryMenusUnit().create_menu(game_window(), imenu_gc, unit, cell));

  AMenuForUnit* unit_menu = graphics_controller->get_unit_menu();
  int side_square_unit_menu = graphics_controller->get_side_square_unit_menu();
  unit_menu->set_geometry(
        {0, size_win.height - side_square_unit_menu * (unit_menu->count_button()+1) - size_bottommenu.height},
        side_square_unit_menu);

  unit_menu->hide();
  unit_menu->show();

  graphics_controller->set_unit_information(new UnitInformation(game_window(), unit->unit));
  graphics_controller->get_unit_information()->set_geometry(
        {0, size_win.height - size_bottommenu.height - side_square_unit_menu}, side_square_unit_menu);
}

void PlayerGraphicsController::do_menu_town(IMenuTownPlayer* player, PlayerTown* town)
{
  auto imenu_gc = graphics_controller->get_imenu_gc_full();
  graphics_controller->set_town_menu(new MenuTown{player, imenu_gc, town});

  Size size_win = graphics_controller->get_size_win();
  Size size_uppermenu = graphics_controller->get_size_uppermenu();
  graphics_controller->get_town_menu()->set_geometry({0, size_uppermenu.height},
                          {size_win.width, size_win.height-size_uppermenu.height});
  graphics_controller->get_town_menu()->start();
  graphics_controller->get_imenu_gc_full()->get_upper_menu()->set_enable_move_map(false);

  graphics_controller->get_imenu_gc_full()->get_bottom_menu()->hide();
  graphics_controller->get_imap_gc_full()->get_minimap()->hide();
  graphics_controller->get_enabled_map() = false;
}

void PlayerGraphicsController::do_menu_science()
{
  graphics_controller->get_imenu_gc_full()->open_menu_science();
}

void PlayerGraphicsController::centering_by_cell(Position pos_cell)
{
  QPoint point = map()->point_of_cell_in_win(pos_cell);

  auto map_gc = graphics_controller->get_imap_gc_full();
  map_gc->move_map(graphics_controller->get_win_map_center() - point);
}

void PlayerGraphicsController::highlight_unit(class Unit* unit, Position pos_cell)
{

  ControlContents controlcontents{map()->cell_by_indexes(pos_cell)};
  controlcontents.set_highlight_unit(unit, true);
}

void PlayerGraphicsController::draw_playermap(PlayerMap* playermap, PlayerScience* player_science)
{
  Position num_cell = graphics_controller->get_num_cell();
  for(size_t i{0}; i < num_cell.x; ++i)
    for(size_t j{0}; j < num_cell.y; ++j)
    {
      ControlContents cc{map()->cell_by_indexes({i,j})};
      cc.set_show_cell(playermap->get_show_cell({i,j}));

      if(cc.has_resource())
          cc.set_show_res(player_science->is_open_resource(cc.get_resource()));
    }
  graphics_controller->get_game_window()->update();
}

IMapForFind* PlayerGraphicsController::mapforfind()
{
  return map();
}

void PlayerGraphicsController::update_res_inform(IMenuTownPlayer* player)
{
  graphics_controller->get_imenu_gc_full()->get_upper_menu()->update_infofm(player);
}

int PlayerGraphicsController::count_cell_resource(Position pos)
{
  ControlContents cc{map()->cell_by_indexes(pos)};
  return cc.get_count_of_res();
}

Resources PlayerGraphicsController::cell_resource(Position pos)
{
  ControlContents cc{map()->cell_by_indexes(pos)};
  return cc.get_resource();
}

bool PlayerGraphicsController::has_cell_building(Position pos)
{
  ControlContents cc{map()->cell_by_indexes(pos)};
  return cc.has_building();
}

Buildings PlayerGraphicsController::cell_building(Position pos)
{
  ControlContents cc{map()->cell_by_indexes(pos)};
  return cc.get_building()->what_building_I();
}

Map* PlayerGraphicsController::map()
{
  return graphics_controller->get_imap_gc_full()->get_map();
}

GameWindow* PlayerGraphicsController::game_window()
{
  return graphics_controller->get_game_window();
}

bool& PlayerGraphicsController::get_is_tracking_unit()
{
  return is_tracking_unit;
}
