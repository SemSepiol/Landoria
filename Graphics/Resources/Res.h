#ifndef RES_H
#define RES_H

#include <QPainter>
#include <QPixmap>

#include "../Factories/FactoryPixmap.h"
#include "../Map/ICell.h"
#include "../IContent.h"
#include "../../Controllers/Enums.h"


class Res : public IContent
{
public:
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override { return Contents::Resource; }
  virtual Resources what_resource_I() const = 0;

  virtual int get_count_of_res() const {return count_of_res;}
  virtual void set_count_of_res(int count_of_res) { count_of_res = count_of_res; }

protected:
  Res(ICell* cell, int count_of_res = 0) : cell{cell}, count_of_res{count_of_res}{}

private:
  ICell* cell;
  int count_of_res;
};

#endif // RES_H
