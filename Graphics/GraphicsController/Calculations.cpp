#include "Calculations.h"
#include <iostream>

Calculations::Calculations(int hexagon_side)
  :side{hexagon_side}
{}

void Calculations::set_side(int hexagon_side)
{
  side = hexagon_side;
}

int Calculations::my_round(double a)
{
  return static_cast<int>(round(a));
}

int Calculations::hexagon_height()
{
  return my_round(side*sqrt(3)/2);
}

int Calculations::hexagon_side()
{
  return side;
}

bool Calculations::point_in_hexagon(QPoint p)
{
  if (abs(p.x()) >= hexagon_height() || abs(p.y()) >= hexagon_side())
    return false;

  pair_of_QPoint vector{QPoint(0,0), p};

  if (check_intersect_of_vectors({point_0(), point_60()}, vector))
    return false;
  if (check_intersect_of_vectors({point_60(), point_120()}, vector))
    return false;
  if (check_intersect_of_vectors({point_120(), point_180()}, vector))
    return false;
  if (check_intersect_of_vectors({point_180(), point_240()}, vector))
    return false;
  if (check_intersect_of_vectors({point_240(), point_300()}, vector))
    return false;
  if (check_intersect_of_vectors({point_300(), point_0()}, vector))
    return false;

  return true;
}

int Calculations::point_in_circle(QPoint point)
{
  for(int i{0}; i < 4; ++i)
  {
    QPoint p = point - point_circle_for_unit(i);
    if (my_round(std::sqrt(p.x()*p.x() + p.y()*p.y())) < circle_radius())
      return i;
  }

  QPoint p = point - point_circle_for_res();
  if (my_round(std::sqrt(p.x()*p.x() + p.y()*p.y())) < circle_radius())
    return 4;

  p = point - point_circle_for_build();
  if (my_round(std::sqrt(p.x()*p.x() + p.y()*p.y())) < circle_radius())
    return 5;

  return -1;
}

QPoint Calculations::point_0()
{
  return {0,-side};
}

QPoint Calculations::point_60()
{
  return {-hexagon_height(), -side/2};
}

QPoint Calculations::point_120()
{
  return {-hexagon_height(), side/2};
}

QPoint Calculations::point_180()
{
  return {0,side};
}

QPoint Calculations::point_240()
{
  return {hexagon_height(), side/2};
}

QPoint Calculations::point_300()
{
  return {hexagon_height(), -side/2};
}

QPoint Calculations::point_circle_for_unit(int num_unit)
{
  switch (num_unit)
  {
  case 0:
    return {-hexagon_height()/3, -side/2};
  case 1:
    return {hexagon_height()/3, -side/2};
  case 2:
    return {-hexagon_height()*2/3, 0};
  case 3:
    return {hexagon_height()*2/3, 0};
  default:
    throw std::runtime_error("The max number of units in a cell is 4");
  }
}

QPoint Calculations::point_circle_for_res()
{
  return {-hexagon_height()/3, side/2};
}

QPoint Calculations::point_circle_for_build()
{
  return {hexagon_height()/3, side/2};
}

int Calculations::circle_radius()
{
  return hexagon_side()/4;
}

int Calculations::vector_product(pair_of_QPoint v1, pair_of_QPoint v2)
{
  int x1 = v1.second.x() - v1.first.x();
  int y1 = v1.second.y() - v1.first.y();
  int x2 = v2.second.x() - v2.first.x();
  int y2 = v2.second.y() - v2.first.y();

  return x1*y2 - x2*y1;
}

bool Calculations::check_intersect_of_vectors(pair_of_QPoint v1, pair_of_QPoint v2)
{
  bool check1_1 = vector_product(v1, {v1.first, v2.first}) < 0;
  bool check1_2 = vector_product(v1, {v1.first, v2.second}) < 0;

  bool check2_1 = vector_product(v2, {v2.first, v1.first}) < 0;
  bool check2_2 = vector_product(v2, {v2.first, v1.second}) < 0;
  return (check1_1^check1_2) && (check2_1^check2_2);
}
