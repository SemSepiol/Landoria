#ifndef IGRAPHICSCONTROLLER_H
#define IGRAPHICSCONTROLLER_H

#include "../DrawWay.h"
#include "../GameWindow.h"
#include "../InformationWidgets/StartMoveInform.h"
#include "../InformationWidgets/UnitInformation.h"
#include "../Map/Map.h"
#include "../Menus/MenuInWindow/BottomMenu.h"
#include "../Menus/MenuInWindow/UpperMenu.h"
#include "../Menus/MenuTown/MenuTown.h"
#include "../Menus/MenuUnit/AMenuForUnit.h"
#include "../Minimap.h"
#include "../../Controllers/IGame.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"


class IGraphicsController : public IObject
{
public:
  virtual Size& get_size_win() = 0;
  virtual Size& get_size_uppermenu() = 0;
  virtual Size& get_size_bottommenu() = 0;
  virtual Size& get_size_win_map() = 0;
  virtual Size& get_size_map() = 0;
  virtual Position& get_num_cell() = 0;
  virtual QPoint& get_map_center() = 0;
  virtual QPoint& get_win_map_center() = 0;
  virtual bool& get_enabled_map() = 0;

  virtual IGameForGraphic* get_game_controller() = 0;

  virtual GameWindow* get_game_window() = 0;
  virtual UpperMenu* get_upper_menu() = 0;
  virtual BottomMenu* get_bottom_menu() = 0;
  virtual Map* get_map() = 0;
  virtual Calculations* get_calc() = 0;

  virtual bool& get_is_tracking_unit() = 0;
  virtual bool& get_is_moving_unit() = 0;
  virtual class Unit*& get_tracking_unit() = 0;
  virtual Position& get_pos_tracking_unit() = 0;

  virtual int& get_side_square_unit_menu() = 0;
  virtual int& get_hexagon_side_minimap() = 0;

  virtual DrawWay* get_drawway() = 0;
  virtual void set_drawway(DrawWay*) = 0;

  virtual AMenuForUnit* get_unit_menu() = 0;
  virtual void set_unit_menu(AMenuForUnit*) = 0;

  virtual UnitInformation* get_unit_information() = 0;
  virtual void set_unit_information(UnitInformation*) = 0;

  virtual MenuTown* get_town_menu() = 0;
  virtual void set_town_menu(MenuTown*) = 0;

  virtual Minimap* get_minimap() = 0;
  virtual StartMoveInform* get_start_move_inform() = 0;

  virtual IWindowGraphicsControllerFull* get_iwindow_gc_full() = 0;
  virtual IMenuGraphicsControllerFull* get_imenu_gc_full() = 0;
  virtual IPlayerGraphicsController* get_iplayer_gc() = 0;
  virtual IMapGraphicsControllerFull* get_imap_gc_full() = 0;
};

#endif // IGRAPHICSCONTROLLER_H
