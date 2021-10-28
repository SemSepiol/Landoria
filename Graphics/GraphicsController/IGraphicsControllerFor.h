#ifndef IGRAPHICSCONTROLLERFOR_H
#define IGRAPHICSCONTROLLERFOR_H

#include <QWidget>
#include <QPoint>
#include <QSize>

#include "../../IObject.h"
#include "Calculations.h"
#include "../../Controllers/Enums.h"
#include "../Units/Unit.h"

class IWindowGraphicsController : public IObject
{
public:
  virtual Size size_win() const = 0;

  virtual void draw_elements() = 0;
  virtual void move_map(QPoint move_point) = 0;
  virtual void resize_map(double coefficient, QPoint pos_mouse) = 0;
  virtual void click(QPoint pos) = 0;
  virtual void start_check_move_unit() = 0;
  virtual void stop_check_move_unit(QPoint mouse_pos) = 0;
  virtual void move_mouse(QPoint new_pos) = 0;
  virtual void press_enter() = 0;

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

  virtual void do_inform_widget(QString text) = 0;
  virtual void del_inform_widget() = 0;
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
  virtual void do_inform_widget(QString text) = 0;
  virtual void del_inform_widget() = 0;
};

#endif // IGRAPHICSCONTROLLERFOR_H
