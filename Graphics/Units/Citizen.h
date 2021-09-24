#ifndef CITIZEN_H
#define CITIZEN_H

#include "Unit.h"
#include "../../Controllers/Enums.h"
#include "../ICell.h"

class Citizen : public Unit
{
public:
  Citizen(ICell* cell) : Unit{cell}{}
  virtual Units what_unit_I() const override { return Units::Citizen; }

};

#endif // CITIZEN_H
