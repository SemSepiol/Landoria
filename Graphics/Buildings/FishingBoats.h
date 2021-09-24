#ifndef FISHING_BOATS_H
#define FISHING_BOATS_H

#include "Building.h"
#include "../../Controllers/Enums.h"
#include "../ICell.h"

class FishingBoats : public Building
{
public:
  FishingBoats(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::FishingBoats; }
};

#endif // FISHING_BOATS_H
