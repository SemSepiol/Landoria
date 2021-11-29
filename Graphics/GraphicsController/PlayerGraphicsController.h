#ifndef PLAYERGRAPHICSCONTROLLER_H
#define PLAYERGRAPHICSCONTROLLER_H

#include "IGraphicsController.h"
#include "IPlayerGraphicsController.h"
#include "IWindowGraphicsController.h"
#include "../Factories/FactoryMenusUnit.h"


class PlayerGraphicsController : public IPlayerGraphicsController
{
public:
  PlayerGraphicsController(IGraphicsController* graphics_controller);
  virtual class Unit* add_unit(Units unit, Position pos_cell) override;

  virtual void move_unit(class Unit* unit, Position old_position, Position new_position) override;
  virtual class Building* build(Buildings building, Position pos_cell) override;
  virtual void del_build(Position pos_cell) override;
  virtual void del_unit(class Unit* unit, Position pos_cell) override;

  virtual void do_menu_unit(PlayerUnit* unit) override;
  virtual void do_menu_town(IMenuTownPlayer* player, PlayerTown* town) override;
  virtual void do_menu_science() override;
  virtual void centering_by_cell(Position pos_cell) override;
  virtual void highlight_unit(class Unit* unit, Position pos) override;
  virtual void draw_playermap(PlayerMap* playermap, PlayerScience* player_science) override;
  virtual IMapForFind* mapforfind() override;

  virtual void update_res_inform(IMenuTownPlayer* player) override;

  virtual int count_cell_resource(Position pos) override;
  virtual Resources cell_resource(Position pos) override;
  virtual bool has_cell_building(Position pos) override;
  virtual Buildings cell_building(Position pos) override;

private:
  Map* map();
  GameWindow* game_window();

  IGraphicsController* graphics_controller;
};

#endif // PLAYERGRAPHICSCONTROLLER_H
