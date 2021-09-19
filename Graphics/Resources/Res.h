#ifndef RES_H
#define RES_H

#include <QPainter>
#include <QPixmap>

#include "IRes.h"
#include "../ICell.h"
#include "../Fubrics/FactoryPixmap.h"

class Res : public IRes
{
public:
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
protected:
  Res(ICell* cell) : cell{cell}{}
private:
  ICell* cell;
};

#endif // RES_H
