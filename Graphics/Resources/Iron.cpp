#include "Iron.h"

void Iron::draw(QPoint point)
{
//  std::cout << point.x() << " " << point.y() << std::endl;
  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);

  qp.drawEllipse(point, rad, rad);
}

QWidget* Iron::window() const
{
  return cell->window();
}

Calculations* Iron::calculations() const
{
  return cell->calculations();
}
