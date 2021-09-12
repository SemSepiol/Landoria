#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <QPoint>
#include <cmath>

class Calculations
{
public:
  Calculations(int hexagon_side = 0);

  void set_side(int hexagon_side);

  int my_round(double a);
  int hexagon_height();
  int hexagon_side();


//функции возвращающие точки относительно центра, число - градусы от вертикали вверх
  QPoint point_0();
  QPoint point_60();
  QPoint point_120();
  QPoint point_180();
  QPoint point_240();
  QPoint point_300();

private:
  int side = 0;
};

#endif // CALCULATIONS_H
