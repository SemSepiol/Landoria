#ifndef IMAPGRAPHICSCONTROLLER_H
#define IMAPGRAPHICSCONTROLLER_H

#include <QWidget>
#include <QPoint>

#include "../../IObject.h"
#include "Calculations.h"

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

class IMapGraphicsControllerFull : public IMapGraphicsController, public IMiniMapGraphicsController
{
public:
  virtual void move_map(double coeffx, double coeffy) = 0;
  virtual void move_map(QPoint move_point) = 0;
  virtual void resize_map(double coefficient, QPoint pos_mouse) = 0;
  virtual void no_highlight_unit(class Unit* unit, Position pos) = 0;
};


#endif // IMAPGRAPHICSCONTROLLER_H
