#ifndef FUBRICBUILD_H
#define FUBRICBUILD_H

#include "../../Controller/Enums.h"
#include "../ICell.h"
#include "../IContent.h"

#include "../Buildings/Town.h"



class FubricBuild : public QObject
{
 public:
  IContent* CreateBuilding(Buildings type_build, ICell* cell) const;
};

#endif // FUBRICBUILD_H
