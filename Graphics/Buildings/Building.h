#ifndef BUILDING_H
#define BUILDING_H

#include <QPainter>

#include "IBuilding.h"
#include "../../Controller/Enums.h"
#include "../Factories/FactoryPixmap.h"
#include "../ICell.h"

class Building : public IBuilding
{
public:
  Building(ICell* cell) : cell{cell}{}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

private:
  ICell* cell;
};

#endif // BUILDING_H
