#ifndef IBUILD_H
#define IBUILD_H

#include "../../Controller/Enums.h"
#include "../IContent.h"

class IBuilding : public IContent
{
public:
  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() const override = 0;
  virtual Calculations* calculations() const override = 0;
  virtual Contents what_content_I() const override {return Contents::Building;}
  virtual Buildings what_building_I() const = 0;
};

#endif // IBUILD_H
