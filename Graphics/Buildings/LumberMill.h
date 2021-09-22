#ifndef LUMBERMILL_H
#define LUMBERMILL_H

#include "Building.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class LumberMill : public Building
{
public:
  LumberMill(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::LumberMill; }
};

#endif // LUMBERMILL_H
