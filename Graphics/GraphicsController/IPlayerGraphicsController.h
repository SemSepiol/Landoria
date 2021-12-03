#ifndef IPLAYERGRAPHICSCONTROLLER_H
#define IPLAYERGRAPHICSCONTROLLER_H

#include "../Map/IMap.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../../Controllers/Player/PlayerMap.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "../../Controllers/Player/PlayerUnit.h"


class IPlayerGraphicsController : public IObject
{
public:
  virtual class Unit* add_unit(Units unit, Position pos_cell) = 0;

  virtual void move_unit(class Unit* unit, Position old_position, Position new_position) = 0;
  virtual class Building* build(Buildings building, Position pos_cell) = 0;
  virtual void del_build(Position pos_cell) = 0;
  virtual void del_unit(class Unit* unit, Position pos_cell) = 0;

  virtual void do_menu_unit(PlayerUnit* unit) = 0;
  virtual void do_menu_town(IMenuTownPlayer* player, PlayerTown* town) = 0;
  virtual void do_menu_science() = 0;
  virtual void centering_by_cell(Position pos_cell) = 0;
  virtual void highlight_unit(class Unit* unit, Position pos) = 0;
  virtual void draw_playermap(PlayerMap* playermap, PlayerScience* player_science) = 0;
  virtual IMapForFind* mapforfind() = 0;
  virtual void update_res_inform(IMenuTownPlayer* player) = 0;

  virtual int count_cell_resource(Position pos) = 0;
  virtual Resources cell_resource(Position pos) = 0;
  virtual bool has_cell_building(Position pos) = 0;
  virtual Buildings cell_building(Position pos) = 0;
};

class IPlayerGraphicsControllerFull : public IPlayerGraphicsController
{
public:
  virtual bool& get_is_tracking_unit() = 0;
};

#endif // IPLAYERGRAPHICSCONTROLLER_H
