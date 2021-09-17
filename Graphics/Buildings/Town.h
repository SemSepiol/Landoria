#ifndef TOWN_H
#define TOWN_H

#include <QPainter>

#include "IBuilding.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Town : public IBuilding
{
public:
  Town(ICell* cell) : cell{cell}{}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Buildings what_building_I() const override { return Buildings::Town; }

private:
  ICell* cell;
};
#endif // TOWN_H
