#ifndef ICELL_H
#define ICELL_H

#include <QPoint>
#include <QWidget>

#include "../GraphicsController/Calculations.h"
#include "../IDrawObject.h"


class ICell : public IDrawObject
{
public:
  enum ShowCell{
    FogOfWar,
    Show,
    NotVisible
  };

  virtual void draw(QPoint point) = 0;
  virtual QWidget* window() const = 0;
  virtual Calculations* calculations() const = 0;
  virtual int count_units() = 0;
};

#endif // ICELL_H
