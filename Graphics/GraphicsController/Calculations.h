#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <cmath>

#include <QPoint>

#include "../../IObject.h"
#include "../../Graphics/Map/TypeMap.h"


class Calculations : public IObject
{
public:
  Calculations(int hexagon_side = 0);

  void set_side(int hexagon_side);
  void set_height(int hexagon_height);

  int my_round(double a);
  int hexagon_height();
  int hexagon_side();

  // точка указывается относительно центра
  bool point_in_hexagon(QPoint point);

  /*
   * точка указывается относительно центра,
   * выдает номер окружности:
   * 0-3: номера окружностей юнитов
   * 4:   номер окружности ресурса
   * 5:   номер окружности строения
   * если точка не в окружностях, то выдает -1
  */
  int point_in_circle(QPoint point, int count_units = 4);


  // функции возвращающие вершины относительно центра, число - градусы от вертикали вверх
  QPoint point_0();
  QPoint point_60();
  QPoint point_120();
  QPoint point_180();
  QPoint point_240();
  QPoint point_300();

  // функции возвращающие центры окружности относительно центра,
  // число - градусы от вертикали вверх
  QPoint point_circle_for_unit(int num_unit, int count_units = 4);
  QPoint point_circle_for_res();
  QPoint point_circle_for_build();

  int circle_radius(int count_units = 4);

  void set_type_content(TypeMap::TypeContent type_content);

private:
  typedef std::pair<QPoint, QPoint> pair_of_QPoint;
  int vector_product(pair_of_QPoint v1, pair_of_QPoint v2);
  bool check_intersect_of_vectors(pair_of_QPoint v1, pair_of_QPoint v2);

  int side = 0;
  TypeMap::TypeContent type_content = TypeMap::All;
};

#endif // CALCULATIONS_H
