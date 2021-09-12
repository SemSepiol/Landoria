#include "Cell.h"
#include <iostream>

Cell::Cell(IMap* map)
  :map{map}
{
}

void Cell::draw(QPoint point)
{
//  std::cout << "c " << point.x() << " " << point.y() << std::endl;
  Calculations* calc = map->calculations();

  QPoint p1 = point - calc->point_0();
  QPoint p2 = point - calc->point_60();
  QPoint p3 = point - calc->point_120();
  QPoint p4 = point - calc->point_180();
  QPoint p5 = point - calc->point_240();
  QPoint p6 = point - calc->point_300();
//  std::cout << p1.x() << " " << p1.y() << std::endl;



  QWidget* win = map->window();
  QPainter qp(win);

  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp.setPen(pen);
  qp.drawLine(p1, p2);
  qp.drawLine(p2, p3);
  qp.drawLine(p3, p4);
  qp.drawLine(p4, p5);
  qp.drawLine(p5, p6);
  qp.drawLine(p6, p1);
}
