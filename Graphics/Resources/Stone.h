#ifndef STONE_H
#define STONE_H

#include <QPainter>

#include "IRes.h"
#include "../../Controller/Enums.h"
#include "../ICell.h"

class Stone : public IRes
{
public:
  Stone(ICell* cell) : cell{cell}{}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Resources what_resource_I() const override { return Resources::Stone; }

private:
  ICell* cell;
};

#endif // STONE_H
