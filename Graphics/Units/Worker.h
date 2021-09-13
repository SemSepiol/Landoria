#ifndef WORKER_H
#define WORKER_H

#include <QPainter>

#include "IUnit.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Worker : public IUnit
{
public:
  Worker(ICell* cell) : cell{cell}{}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Units what_unit_I() const override { return Units::Worker; }

private:
  ICell* cell;
};

#endif // WORKER_H
