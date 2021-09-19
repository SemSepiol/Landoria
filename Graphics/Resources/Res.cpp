#include "Res.h"

void Res::draw(QPoint point)
{
  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);

  qp.drawEllipse(point, rad, rad);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_res(what_resource_I());
  QRectF source{0., 0., 188., 188.};
  int adjustment = rad/10;
  QRectF target{(point.x() - rad - adjustment)*1., (point.y() - rad - adjustment)*1., 2.*(rad+adjustment), 2.*(rad+adjustment)};
  qp.drawPixmap(target, pixmap, source);
}

QWidget* Res::window() const
{
  return cell->window();
}

Calculations* Res::calculations() const
{
  return cell->calculations();
}
