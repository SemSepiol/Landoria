#ifndef FISHING_BOATS_H
#define FISHING_BOATS_H

#include "Building.h"
#include "../Map/ICell.h"
#include "../../Controllers/Enums.h"


class FishingBoat : public Building
{
public:
  FishingBoat(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::FishingBoat; }
};

#endif // FISHING_BOATS_H
