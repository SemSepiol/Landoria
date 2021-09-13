#ifndef IDRAW_OBJECT_H
#define IDRAW_OBJECT_H
#include <memory>
#include <QWidget>
#include <QPoint>

#include "../Controller/Calculations.h"
#include "../IObject.h"

class IDrawObject : public IObject
{
public:
  IDrawObject(){}

  virtual void draw(QPoint point) = 0;
  virtual QWidget* window() const = 0;
  virtual Calculations* calculations() const = 0;

  virtual ~IDrawObject() {}
};

#endif // IDRAW_OBJECT_H
