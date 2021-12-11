#ifndef FUBRICBUILD_H
#define FUBRICBUILD_H


#include "../Buildings/Farm.h"
#include "../Buildings/FishingBoat.h"
#include "../Buildings/Fort.h"
#include "../Buildings/LumberMill.h"
#include "../Buildings/Mine.h"
#include "../Buildings/OilWell.h"
#include "../Buildings/Pasture.h"
#include "../Buildings/Quarry.h"
#include "../Buildings/Town.h"
#include "../Buildings/TradingPost.h"
#include "../IContent.h"
#include "../Map/ICell.h"
#include "../../Controllers/Enums.h"


class FactoryBuild : public QObject
{
 public:
  IContent* create_building(Buildings type_build, ICell* cell) const;
};

#endif // FUBRICBUILD_H
