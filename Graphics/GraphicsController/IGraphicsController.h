#ifndef IGRAPHICSCONTROLLER_H
#define IGRAPHICSCONTROLLER_H

#include <QWidget>
#include <QPoint>
#include <QSize>

#include "../../IObject.h"
#include "Calculations.h"
#include "../../Controllers/Enums.h"
#include "../Units/Unit.h"
#include "../../Controllers/IPlayer.h"

class IGraphicsControllerForWindow : public IObject
{
public:
  virtual int width_win() const = 0;
  virtual int height_win() const = 0;

  virtual void draw_map() = 0;
  virtual void move_map(QPoint move_point) = 0;
  virtual void resize_map(double coefficient) = 0;
  virtual void click(QPoint pos) = 0;
};

class IGraphicsControllerForMap : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual Calculations* calculations() const = 0;

  virtual int count_cell_x() const = 0;
  virtual int count_cell_y() const = 0;

  virtual int width_map() const = 0;
  virtual int height_map() const = 0;
  virtual int width_win_map() const = 0;
  virtual int height_win_map() const = 0;
  virtual QPoint win_map_center() const = 0;
};

class IGraphicsControllerForMenuInWindow : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual void exit() = 0;
  virtual void show_minimap() = 0;
};

class IGraphicsControllerForPlayer : public IObject
{
public:
  virtual class Unit* add_unit(Units unit, size_t cell_x, size_t cell_y) = 0;
  virtual void move_unit(class Unit* unit, size_t old_position_x, size_t old_position_y,
                         size_t new_position_x, size_t new_position_y) = 0;
  virtual void del_unit(class Unit* unit, size_t cell_x, size_t cell_y) = 0;

  virtual void do_menu_unit(IPlayerForMenu* player, class Unit*) = 0;
};

class IGraphicsControllerForMiniMap : public IObject
{
public:
  virtual int count_cell_x() const = 0;
  virtual int count_cell_y() const = 0;

  // coeffx = new_map_center.x / width_map
  // coeffy = new_map_center.y / height_map
  virtual void move_map(double coeffx, double coeffy) = 0;
};

#endif // IGRAPHICSCONTROLLER_H
