#ifndef IGAME_H
#define IGAME_H

#include "../IObject.h"

class IGameForGraphic : public IObject
{
public:
  virtual int count_cell_x() const = 0;
  virtual int count_cell_y() const = 0;
  virtual int width_win() const = 0;
  virtual int height_win() const = 0;
  virtual void exit() = 0;
};

#endif // IGAME_H
