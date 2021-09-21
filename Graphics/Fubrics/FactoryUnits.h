#ifndef FABRICUNITS_H
#define FABRICUNITS_H

#include "../../Controller/Enums.h"
#include "../ICell.h"
#include "../IContent.h"

#include "../Units/Worker.h"
#include "../Units/Citizen.h"
#include "../Units/Swordsman.h"
#include "../Units/Bowman.h"


class FubricUnits : public QObject
{
 public:
  IContent* create_unit(Units type_unit, ICell* cell) const;
};


#endif // FUBRICUNITS_H
