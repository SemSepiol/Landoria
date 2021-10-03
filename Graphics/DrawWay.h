#ifndef DRAWWAY_H
#define DRAWWAY_H

#include <QWidget>
#include <QPainter>

#include "IObject.h"
#include "Map.h"
#include "../Controllers/FindUnitWay.h"
#include "Units/Unit.h"

class DrawWay : public IObject
{
public:
  DrawWay(QWidget* win, Map* map, Position start_way, class Unit* unit);
  void set_end_way(Position end_way);
  void draw();

private:
  void draw_circle(QPoint pos);
  QWidget* win;
  Map* map;
  Position start_way;
  class Unit* unit;
  Position end_way;
};

#endif // DRAWWAY_H
