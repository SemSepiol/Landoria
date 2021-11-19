#ifndef FABRICUNITS_H
#define FABRICUNITS_H

#include "../ICell.h"
#include "../IContent.h"
#include "../Units/Bowman.h"
#include "../Units/Citizen.h"
#include "../Units/Swordsman.h"
#include "../Units/Worker.h"
#include "../../Controllers/Enums.h"


class FactoryUnits : public QObject
{
public:
  IContent* create_unit(Units type_unit, ICell* cell) const;
};


#endif // FUBRICUNITS_H
