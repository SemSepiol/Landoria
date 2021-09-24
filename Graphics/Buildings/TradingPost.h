#ifndef TRADINGPOST_H
#define TRADINGPOST_H

#include "Building.h"
#include "../../Controllers/Enums.h"
#include "../ICell.h"

class TradingPost : public Building
{
public:
  TradingPost(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::TradingPost; }
};

#endif // TRADINGPOST_H
