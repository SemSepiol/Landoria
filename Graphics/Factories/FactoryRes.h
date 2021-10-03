#ifndef FUBRICRES_H
#define FUBRICRES_H

#include "../../Controllers/Enums.h"
#include "../ICell.h"
#include "../IContent.h"

#include "../Resources/Iron.h"
#include "../Resources/Gold.h"
#include "../Resources/Stone.h"
#include "../Resources/Aluminum.h"
#include "../Resources/Horses.h"
#include "../Resources/Oil.h"
#include "../Resources/Uranium.h"
#include "../Resources/Coal.h"
#include "../Resources/Fish.h"
#include "../Resources/Silver.h"



class FactoryRes : public QObject
{
 public:
  IContent* create_res(Resources type_res, ICell* cell, int count_of_res) const;
};


#endif // FUBRICRES_H
