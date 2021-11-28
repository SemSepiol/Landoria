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
  virtual TypeUnit what_my_type() const override { return Peaceful; }

  virtual void set_standard_charaterichtics() override;
  void set_build_speed(int _build_speed);
  int get_build_speed() const;
private:
  int build_speed;
};

#endif // WORKER_H
