#ifndef RES_H
#define RES_H

#include <QPainter>
#include <QPixmap>

#include "../IContent.h"
#include "../ICell.h"
#include "../../Controller/Enums.h"
#include "../Factories/FactoryPixmap.h"

class Res : public IContent
{
public:
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override {return Contents::Resource;}
  virtual Resources what_resource_I() const = 0;

protected:
  Res(ICell* cell) : cell{cell}{}
private:
  ICell* cell;
};

#endif // RES_H
