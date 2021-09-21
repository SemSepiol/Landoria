#ifndef UNIT_H
#define UNIT_H

#include <QPainter>

#include "IUnit.h"
#include "../Fubrics/FactoryPixmap.h"
#include "../ICell.h"

class Unit : public IUnit
{
public:
  Unit(ICell* cell) : cell{cell}{}
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

private:
  ICell* cell;
};

#endif // UNIT_H
