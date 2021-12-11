#ifndef QUARRY_H
#define QUARRY_H

#include "Building.h"
#include "../Map/ICell.h"
#include "../../Controllers/Enums.h"


class Quarry : public Building
{
public:
  Quarry(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::Quarry; }
};

#endif // QUARRY_H
