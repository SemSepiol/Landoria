#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <QPoint>
#include <cmath>
#include "../IObject.h"

class Calculations : public IObject
{
public:
  Calculations(int hexagon_side = 0);

  void set_side(int hexagon_side);

  int my_round(double a);
  int hexagon_height();
  int hexagon_side();


//функции возвращающие вершины относительно центра, число - градусы от вертикали вверх
  QPoint point_0();
  QPoint point_60();
  QPoint point_120();
  QPoint point_180();
  QPoint point_240();
  QPoint point_300();

// функции возвращающие центры окружности относительно центра,
// число - градусы от вертикали вверх


  QPoint point_circle_for_unit(int num_unit);
  QPoint point_circle_for_res();
  QPoint point_circle_for_build();

  int circle_radius();

private:
  int side = 0;
};

#endif // CALCULATIONS_H
