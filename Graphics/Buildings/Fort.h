#ifndef FORT_H
#define FORT_H

#include "Building.h"
#include "../ICell.h"
#include "../../Controllers/Enums.h"


class Fort : public Building
{
public:
  Fort(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::Fort; }
};

#endif // FORT_H
