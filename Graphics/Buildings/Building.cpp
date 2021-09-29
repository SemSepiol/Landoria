#include "Building.h"

void Building::draw(QPoint point)
{
  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp.drawEllipse(point, rad, rad);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_building(what_building_I());
  QRectF source = FactoryPixmap().size_picture_content();
  int adjustment = rad/10;
  QRectF target{(point.x() - rad - adjustment)*1., (point.y() - rad - adjustment)*1., 2.*(rad+adjustment), 2.*(rad+adjustment)};
  qp.drawPixmap(target, pixmap, source);
}

QWidget* Building::window() const
{
  return cell->window();
}

Calculations* Building::calculations() const
{
  return cell->calculations();
}
