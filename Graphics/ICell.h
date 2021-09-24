#ifndef ICELL_H
#define ICELL_H

#include <QPoint>
#include <QWidget>

#include "IDrawObject.h"
#include "GraphicsController/Calculations.h"


class ICell : public IDrawObject
{
public:
  virtual void draw(QPoint point) = 0;
  virtual QWidget* window() const = 0;
  virtual Calculations* calculations() const = 0;
};

#endif // ICELL_H
