#include "Unit.h"

Unit::Unit(ICell* _cell)
  : cell{_cell}
{}

void Unit::draw(QPoint point)
{
  int rad = calculations()->circle_radius(cell->count_units());

  QPainter qp(window());
  QPen pen(Qt::black, 2, Qt::SolidLine);
  qp.setBrush(QBrush(FactoryColor().country_color(country)));
  qp.drawEllipse(point, rad, rad);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_unit_on_map(what_unit_I());
  QRectF source = FactoryPixmap().size_picture_content();
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

void Unit::set_standard_charaterichtics()
{
  auto uc = UnitsCharaterichtics();
  max_health = uc.get_unit_max_health(what_unit_I());
  health = uc.get_unit_max_health(what_unit_I());
  max_movement = uc.get_unit_max_movement(what_unit_I());
  movement = uc.get_unit_max_movement(what_unit_I());
  vision = uc.get_unit_vision(what_unit_I());
}


void Unit::set_health(int _health)
{
  health = _health;
}

int Unit::get_health() const
{
  return health;
}

void Unit::set_max_health(int _max_health)
{
  max_health = _max_health;
}

int Unit::get_max_health() const
{
  return max_health;
}

void Unit::set_movement(int _movement)
{
  movement = _movement;
}

int Unit::get_movement() const
{
  return movement;
}

void Unit::set_max_movement(int _max_movement)
{
  max_movement = _max_movement;
}

int Unit::get_max_movement() const
{
  return max_movement;
}

void Unit::set_vision(int _vision)
{
  vision = _vision;
}

int Unit::get_vision() const
{
  return vision;
}

void Unit::set_country(Countries _country)
{
  country = _country;
}

Countries Unit::get_country() const
{
  return country;
}

