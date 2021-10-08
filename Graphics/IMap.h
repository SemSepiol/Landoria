#ifndef IMAP_H
#define IMAP_H
#include <QPoint>
#include <QWidget>

#include "IDrawObject.h"
#include "GraphicsController/Calculations.h"

class IMap : public IDrawObject
{
public:
  // point - центр карты
  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() const override = 0;
  virtual Calculations* calculations() const override = 0;
};

#endif // IMAP_H
