#ifndef WORKER_H
#define WORKER_H

#include "Unit.h"
#include "../../Controllers/Enums.h"


class Worker : public Unit
{
public:
  Worker(ICell* cell)
    : Unit{cell}{}
  virtual Units what_unit_I() const override { return Units::Worker; }

  void set_build_speed(int _build_speed) { build_speed = _build_speed; }
  int get_build_speed() const { return build_speed; }
private:
  int build_speed;
};

#endif // WORKER_H
