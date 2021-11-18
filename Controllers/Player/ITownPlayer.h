#ifndef ITOWNPLAYER_H
#define ITOWNPLAYER_H

#include "../../IObject.h"
#include "../Enums.h"

class ITownPlayer : public IObject
{
public:
  virtual void add_unit(Units type_unit, Position pos_cell) = 0;
  virtual Countries get_country() const = 0;
};

#endif // ITOWNPLAYER_H
