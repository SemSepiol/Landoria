#ifndef FUBRICRES_H
#define FUBRICRES_H

#include "../../Controller/Enums.h"
#include "../ICell.h"
#include "../IContent.h"

#include "../Resources/Iron.h"
#include "../Resources/Stone.h"
#include "../Resources/Gold.h"


class FubricRes : public QObject
{
 public:
  IContent* CreateRes(Resources type_res, ICell* cell) const;
};


#endif // FUBRICRES_H
