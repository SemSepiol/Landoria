#ifndef BOWMAN_H
#define BOWMAN_H

#include "Unit.h"
#include "../../Controllers/Enums.h"


class Bowman : public Unit
{
public:
  Bowman(ICell* cell)
    : Unit{cell}{}
  virtual Units what_unit_I() const override { return Units::Bowman; }
};


#endif // BOWMAN_H
