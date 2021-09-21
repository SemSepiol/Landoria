#ifndef WORKER_H
#define WORKER_H


#include "Unit.h"
#include "../../Controller/Enums.h"


class Worker : public Unit
{
public:
  Worker(ICell* cell) : Unit{cell}{}
  virtual Units what_unit_I() const override { return Units::Worker; }
};

#endif // WORKER_H
