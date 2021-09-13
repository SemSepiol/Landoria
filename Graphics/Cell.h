#ifndef CELL_H
#define CELL_H
#include <memory>
#include <vector>
#include <QPainter>
#include <QWidget>

#include "IMap.h"
#include "ICell.h"
#include "IContent.h"
#include "../Controller/Enums.h"
#include "../Controller/Calculations.h"
#include "../Controller/FactoryContents.h"

class Cell : public ICell
{
public:
  Cell(IMap* map);

  // point - центр клетки
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
private:
  IMap* map;
  std::vector<std::unique_ptr<IContent>> contents;
};

#endif // CELL_H
