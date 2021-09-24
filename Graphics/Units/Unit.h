#ifndef UNIT_H
#define UNIT_H

#include <QPainter>

#include "../IContent.h"
#include "../../Controller/Enums.h"
#include "../Factories/FactoryPixmap.h"
#include "../ICell.h"

class Unit : public IContent
{
public:
  Unit(ICell* cell) : cell{cell}{}
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override {return Contents::Unit;}
  virtual Units what_unit_I() const = 0;
private:
  ICell* cell;
};

#endif // UNIT_H
