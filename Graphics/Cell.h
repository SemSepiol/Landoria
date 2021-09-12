#ifndef CELL_H
#define CELL_H
#include <memory>
#include <QPainter>

#include "IDrawObject.h"
#include "IMap.h"
#include "../Controller/Calculations.h"

class Cell : public IDrawObject
{
public:
  Cell(IMap* map);

  // point - центр клетки
  virtual void draw(QPoint point) override;

private:
  IMap* map;
};

#endif // CELL_H
