#ifndef IGAME_H
#define IGAME_H

#include <QWidget>
#include <QSize>

#include "../IObject.h"
#include "Calculations.h"

class IGame : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual Calculations* calculations() const = 0;

  virtual int count_cell_x() const = 0;
  virtual int count_cell_y() const = 0;

  virtual int width_win() const = 0;
  virtual int height_win() const = 0;
  virtual int width_map() const = 0;
  virtual int height_map() const = 0;

  virtual void draw_map() = 0;
protected:
  IGame(){}
};

#endif // IGAME_H
