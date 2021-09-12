#include "Calculations.h"

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
