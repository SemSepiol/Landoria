#include "Worker.h"
#include <iostream>

void Worker::draw(QPoint point)
{
//  std::cout << point.x() << " " << point.y() << std::endl;
  int rad = calculations()->circle_radius();

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);

  qp.drawEllipse(point, rad, rad);
}

QWidget* Worker::window() const
{
  return cell->window();
}

Calculations* Worker::calculations() const
{
  return cell->calculations();
}
