#ifndef BUILDING_H
#define BUILDING_H

#include <QPainter>

#include "../../Controller/Enums.h"
#include "../Factories/FactoryPixmap.h"
#include "../ICell.h"
#include "../IContent.h"

class Building : public IContent
{
public:
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override {return Contents::Building;}
  virtual Buildings what_building_I() const = 0;

protected:
  Building(ICell* cell) : cell{cell}{}
private:
  ICell* cell;
};

#endif // BUILDING_H
