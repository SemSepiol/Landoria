#ifndef FARM_H
#define FARM_H

#include "Building.h"
#include "../ICell.h"
#include "../../Controllers/Enums.h"


class Farm : public Building
{
public:
  Farm(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::Farm; }
};

#endif // FARM_H
