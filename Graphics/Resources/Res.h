#ifndef RES_H
#define RES_H

#include <QPainter>
#include <QPixmap>

#include "../IContent.h"
#include "../ICell.h"
#include "../../Controllers/Enums.h"
#include "../Factories/FactoryPixmap.h"

class Res : public IContent
{
public:
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override { return Contents::Resource; }
  virtual Resources what_resource_I() const = 0;
  virtual int count_of_res() const {return _count_of_res;}
  virtual void set_count_of_res(int count_of_res) { _count_of_res = count_of_res; }

protected:
  Res(ICell* cell, int count_of_res = 0) : cell{cell}, _count_of_res{count_of_res}{}

private:
  ICell* cell;
  int _count_of_res;
};

#endif // RES_H
