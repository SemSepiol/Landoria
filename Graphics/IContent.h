#ifndef ICONTENT_H
#define ICONTENT_H

#include "../Controllers/Enums.h"
#include "IDrawObject.h"

class IContent : public IDrawObject
{
public:
  virtual void draw(QPoint point) = 0;
  virtual QWidget* window() const = 0;
  virtual Calculations* calculations() const = 0;
  virtual Contents what_content_I() const = 0;
};

#endif // ICONTENT_H
