#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "Unit.h"
#include "../../Controller/Enums.h"


class Swordsman : public Unit
{
public:
  Swordsman(ICell* cell) : Unit{cell}{}
  virtual Units what_unit_I() const override { return Units::Swordsman; }
};

#endif // SWORDSMAN_H
