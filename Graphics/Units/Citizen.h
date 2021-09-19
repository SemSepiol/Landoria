#ifndef CITIZEN_H
#define CITIZEN_H

#include <QPainter>

#include "IUnit.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Citizen : public IUnit
{
public:
  Citizen(ICell* cell) : cell{cell}{}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Units what_unit_I() const override { return Units::Citizen; }

private:
  ICell* cell;
};

#endif // CITIZEN_H
