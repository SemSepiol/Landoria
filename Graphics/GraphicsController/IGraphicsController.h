#ifndef IGRAPHICSCONTROLLER_H
#define IGRAPHICSCONTROLLER_H

#include <QWidget>
#include <QPoint>
#include <QSize>

#include "../../IObject.h"
#include "Calculations.h"
#include "../../Controllers/Enums.h"
#include "../Units/Unit.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "../../Controllers/Player/PlayerMap.h"
#include "../../Controllers/Player/PlayerUnit.h"
#include "../IMap.h"


class IWindowGraphicsController : public IObject
{
public:
  virtual Size size_win() const = 0;

  virtual void draw_elements() = 0;
  virtual void move_map(QPoint move_point) = 0;
  virtual void resize_map(double coefficient) = 0;
  virtual void click(QPoint pos) = 0;
  virtual void start_check_move_unit() = 0;
  virtual void stop_check_move_unit(QPoint mouse_pos) = 0;
  virtual void move_mouse(QPoint new_pos) = 0;

  virtual int map_upper_edge() const = 0;
  virtual int map_bottom_edge() const = 0;
};

class IMapGraphicsController : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual Calculations* calculations() const = 0;

  virtual size_t count_cell_x() const = 0;
  virtual size_t count_cell_y() const = 0;

  virtual Size size_map() const = 0;
  virtual Size size_win_map() const  = 0;
  virtual QPoint win_map_center() const = 0;
  virtual QPoint map_center() const = 0;
};

class IMenuInWindowGraphicsController : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual void move_map(QPoint move_point) = 0;
  virtual void exit() = 0;
  virtual void show_minimap() = 0;
  virtual void next_move() = 0;
};

class IPlayerGraphicsController : public IObject
{
public:
  virtual class Unit* add_unit(Units unit, Position pos_cell) = 0;

  virtual void move_unit(class Unit* unit, Position old_position, Position new_position) = 0;
  virtual class Building* build(Buildings building, Position pos_cell) = 0;
  virtual void del_build(Position pos_cell) = 0;
  virtual void del_unit(class Unit* unit, Position pos_cell) = 0;

  virtual void do_menu_unit(PlayerUnit* unit) = 0;
  virtual void do_menu_town(PlayerTown* town) = 0;
  virtual void centering_by_cell(Position pos_cell) = 0;
  virtual void highlight_unit(class Unit* unit, Position pos) = 0;
  virtual void draw_playermap(PlayerMap* playermap) = 0;
  virtual IMapForFind* mapforfind() const = 0;
};

class IMiniMapGraphicsController : public IObject
{
public:
  virtual size_t count_cell_x() const = 0;
  virtual size_t count_cell_y() const = 0;

  /*
   *  coeffx = new_map_center.x / width_map
   * coeffy = new_map_center.y / height_map
  */
  virtual void move_map(double coeffx, double coeffy) = 0;
};

class IUnitMenuGraphicsController : public IObject
{
public:
  virtual void menu_unit_event(class Unit* unit, Event* event) = 0;
};

class ITownMenuGraphicsController : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual void delete_townmenu() = 0;
};

#endif // IGRAPHICSCONTROLLER_H
