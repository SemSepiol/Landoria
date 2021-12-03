#include "Res.h"

void Res::draw(QPoint point)
{
  if(!pixmap_for_res)
    pixmap_for_res.reset(new  QPixmap{FactoryPixmap().create_pixmap_for_res(what_resource_I())});

  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);

  qp.drawEllipse(point, rad, rad);

  QRectF source  = FactoryPixmap().size_picture_content();
  int adjustment = rad/10;
  QRectF target{(point.x() - rad - adjustment)*1., (point.y() - rad - adjustment)*1., 2.*(rad+adjustment), 2.*(rad+adjustment)};
  qp.drawPixmap(target, *pixmap_for_res.get(), source);
}

QWidget* Res::window() const
{
  return cell->window();
}

Calculations* Res::calculations() const
{
  return cell->calculations();
}

Res::Res(ICell* cell, int count_of_res)
  :cell{cell}, count_of_res{count_of_res}
{}
