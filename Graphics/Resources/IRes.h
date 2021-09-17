#ifndef IRESOURCE_H
#define IRESOURCE_H

#include "../../Controller/Enums.h"
#include "../IContent.h"

class IRes : public IContent
{
public:
  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() const override = 0;
  virtual Calculations* calculations() const override = 0;
  virtual Contents what_content_I() const override {return Contents::Resource;}
  virtual Resources what_resource_I() const = 0;
};

#endif // IRESOURCE_H
