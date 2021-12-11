#ifndef IWINDOWGRAPHICSCONTROLLER_H
#define IWINDOWGRAPHICSCONTROLLER_H

#include <QPoint>
#include <QWidget>

#include "../../IObject.h"


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
  virtual void press_escape() = 0;

  virtual int map_upper_edge() const = 0;
  virtual int map_bottom_edge() const = 0;
};

class IWindowGraphicsControllerFull : public IWindowGraphicsController
{
public:
  virtual void start_check_move_unit() = 0;
  virtual void stop_check_move_unit(QPoint mouse_pos) = 0;

  virtual void start_check_move_unit(class Unit* unit) = 0;
  virtual void stop_check_move_unit() = 0;
};

#endif // IWINDOWGRAPHICSCONTROLLER_H
