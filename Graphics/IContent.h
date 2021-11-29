#ifndef ICONTENT_H
#define ICONTENT_H

#include "../Controllers/Enums.h"
#include "IDrawObject.h"


class IContent : public IDrawObject
{
public:
  enum TypeDraw
  {
    FullCell,
    PartCell
  };

  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() const override = 0;
  virtual Calculations* calculations() const override = 0;
  virtual Contents what_content_I() const = 0;

  virtual void set_type_draw(TypeDraw _type_draw)
  { type_draw = _type_draw; }

protected:
  TypeDraw type_draw = PartCell;
};

#endif // ICONTENT_H
