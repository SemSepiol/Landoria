#include "Building.h"

void Building::draw(QPoint point)
{
  int rad = calculations()->circle_radius();

  if(phase < end_phase)
    draw_build_phase(point);

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_building(what_building_I());
  QRectF source = FactoryPixmap().size_picture_content();
  int adjustment = rad/10;
  QRectF target{(point.x() - rad - adjustment)*1., (point.y() - rad - adjustment)*1., 2.*(rad+adjustment), 2.*(rad+adjustment)};
  qp.drawPixmap(target, pixmap, source);

  if(phase < end_phase)
    qp.setBrush(QBrush(QColor(100, 100, 255, 200)));
  qp.drawEllipse(point, rad, rad);
}

QWidget* Building::window() const
{
  return cell->window();
}

Calculations* Building::calculations() const
{
  return cell->calculations();
}

void Building::set_build_phase(int _phase)
{
  if(_phase < end_phase)
    phase = _phase;
  else
    phase = end_phase;
}

int Building::get_build_phase() const
{
  return phase;
}

void Building::set_end_build_phase(int _end_phase)
{
  end_phase = _end_phase;
}

int Building::get_end_build_phase() const
{
  return end_phase;
}

bool Building::is_built() const
{
  return end_phase == phase;
}

void Building::draw_build_phase(QPoint point)
{
  int rad = calculations()->circle_radius();
  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);


  QRect rect1{QPoint{point.x() - rad, point.y() - rad - rad/5},
              QPoint{point.x() + rad, point.y() - rad}};

  QRect rect2{QPoint{point.x() - rad, point.y() - rad - rad/5},
              QPoint{point.x() - rad + 2*rad*phase/end_phase, point.y() - rad}};

  qp.drawRect(rect1);
  qp.setBrush(QBrush(Qt::blue));
  qp.drawRect(rect2);
}
