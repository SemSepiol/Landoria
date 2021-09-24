#ifndef MINE_H
#define MINE_H

#include "Building.h"
#include "../../Controllers/Enums.h"
#include "../ICell.h"

class Mine : public Building
{
public:
  Mine(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::Mine; }
};

#endif // MINE_H
