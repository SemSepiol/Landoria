#ifndef IRON_H
#define IRON_H

#include <QPainter>

#include "IRes.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Iron : public IRes
{
public:
  Iron(ICell* cell) : cell{cell}{}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Resources what_resource_I() const override { return Resources::Iron; }

private:
  ICell* cell;
};

#endif // IRON_H
