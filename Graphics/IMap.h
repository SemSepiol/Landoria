#ifndef IMAP_H
#define IMAP_H
#include <QPoint>
#include <QWidget>

#include "IDrawObject.h"
#include "GraphicsController/Calculations.h"
#include "ICell.h"

class IMapForFind : public IObject
{
public:
  virtual ICell* icell_by_indexes(Position pos) const = 0;
  virtual std::vector<Position> adjacent_cells(Position pos) const = 0;
};

class IMap : public IDrawObject
{
public:
  // point - центр карты
  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() const override = 0;
  virtual Calculations* calculations() const override = 0;
};

#endif // IMAP_H
