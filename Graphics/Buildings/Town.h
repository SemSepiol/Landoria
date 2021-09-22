#ifndef TOWN_H
#define TOWN_H

#include "Building.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Town : public Building
{
public:
  Town(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::Town; }
};

#endif // TOWN_H
