#ifndef CELL_H
#define CELL_H
#include <memory>

#include "IDrawObject.h"
#include "IMap.h"

class Cell : public IDrawObject
{
public:
  Cell(IMap* map);

  virtual void draw(QPoint point) override;

private:
  std::unique_ptr<IMap> _map;
};

#endif // CELL_H
