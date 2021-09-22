#ifndef PASTURE_H
#define PASTURE_H

#include "Building.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Pasture : public Building
{
public:
  Pasture(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::Pasture; }
};

#endif // PASTURE_H
