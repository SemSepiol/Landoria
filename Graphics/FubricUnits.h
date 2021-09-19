#ifndef FABRICUNITS_H
#define FABRICUNITS_H

#include "Controller/Enums.h"
#include "ICell.h"
#include "IContent.h"

#include "Units/Worker.h"


class FubricUnits : public QObject
{
 public:
  IContent* CreateUnit(Units type_unit, ICell* cell) const;
};




#endif // FABRICUNITS_H
