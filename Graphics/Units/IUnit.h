#ifndef IUNIT_H
#define IUNIT_H

#include "../../Controllers/Enums.h"
#include "../IContent.h"

class IUnit : public IContent
{
public:
  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() const override = 0;
  virtual Calculations* calculations() const override = 0;
  virtual Contents what_content_I() const override {return Contents::Unit;}
  virtual Units what_unit_I() const = 0;
};

#endif // IUNIT_H
