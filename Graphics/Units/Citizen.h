#ifndef CITIZEN_H
#define CITIZEN_H

#include "Unit.h"
#include "../../Controllers/Enums.h"


class Citizen : public Unit
{
public:
  Citizen(ICell* cell)
    : Unit{cell}{}
  virtual Units what_unit_I() const override { return Units::Citizen; }
  virtual TypeUnit what_my_type() const override { return Peaceful; }
};

#endif // CITIZEN_H
