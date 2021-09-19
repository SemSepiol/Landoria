#ifndef GOLD_H
#define GOLD_H

#include <QPainter>

#include "IRes.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Gold : public IRes
{
public:
  Gold(ICell* cell) : cell{cell}{}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Resources what_resource_I() const override { return Resources::Gold; }

private:
  ICell* cell;
};

#endif // GOLD_H
