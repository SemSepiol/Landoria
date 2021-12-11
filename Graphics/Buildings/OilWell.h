#ifndef OILWELL_H
#define OILWELL_H

#include "Building.h"
#include "../Map/ICell.h"
#include "../../Controllers/Enums.h"


class OilWell : public Building
{
public:
  OilWell(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::OilWell; }
};

#endif // OILWELL_H
