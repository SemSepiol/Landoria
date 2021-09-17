#include "Town.h"

void Town::draw(QPoint point)
{
//  std::cout << point.x() << " " << point.y() << std::endl;
  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);

  qp.drawEllipse(point, rad, rad);
}

QWidget* Town::window() const
{
  return cell->window();
}

Calculations* Town::calculations() const
{
  return cell->calculations();
}
