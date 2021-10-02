#ifndef FUBRICBUILD_H
#define FUBRICBUILD_H

#include "../../Controllers/Enums.h"
#include "../ICell.h"
#include "../IContent.h"

#include "../Buildings/Town.h"
#include "../Buildings/Farm.h"
#include "../Buildings/FishingBoat.h"
#include "../Buildings/Fort.h"
#include "../Buildings/LumberMill.h"
#include "../Buildings/Mine.h"
#include "../Buildings/OilWell.h"
#include "../Buildings/Pasture.h"
#include "../Buildings/Quarry.h"
#include "../Buildings/TradingPost.h"



class FactoryBuild : public QObject
{
 public:
  IContent* create_building(Buildings type_build, ICell* cell) const;
};

#endif // FUBRICBUILD_H
