#include "Unit.h"

void Unit::draw(QPoint point)
{
  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp.setBrush(QBrush (Qt::yellow));
  qp.drawEllipse(point, rad, rad);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_unit(what_unit_I());
  QRectF source{0., 0., 188., 188.};
  int adjustment = 0;
  int a = static_cast<int>(round(rad/sqrt(2)));
  QRectF target{(point.x() - a - adjustment)*1., (point.y() - a - adjustment)*1., 2.*(a+adjustment), 2.*(a+adjustment)};
  qp.drawPixmap(target, pixmap, source);
}

QWidget* Unit::window() const
{
  return cell->window();
}

Calculations* Unit::calculations() const
{
  return cell->calculations();
}
