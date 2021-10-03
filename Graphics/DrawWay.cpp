#include "DrawWay.h"
#include <iostream>

DrawWay::DrawWay(QWidget* _win, Map* _map, Position _start_way, class Unit* _unit)
  :win{_win}, map{_map}, start_way{_start_way}, unit{_unit}
{}

void DrawWay::set_end_way(Position _end_way)
{
  end_way = _end_way;
}

void DrawWay::draw()
{
  Way way = FindUnitWay().get_way(unit, map, start_way, end_way);
  for(size_t i{0}; i < way.get_count_moves_in_way(); ++i)
  {
    OneMove onemove = way.get_move_in_way(i);
    std::vector<Position> minimove = onemove.minimove;
    for(size_t j{0}; j < minimove.size()-1; ++j)
      draw_circle(map->point_of_cell_in_win(minimove[j].x, minimove[j].y));
  }
  draw_circle(map->point_of_cell_in_win(end_way.x, end_way.y));
}

void DrawWay::draw_circle(QPoint pos)
{
  QPainter qp(win);
  QPen pen(Qt::blue, 2, Qt::SolidLine);
  qp.setPen(pen);
  QBrush brush(Qt::blue);
  qp.setBrush(brush);
  int rad = map->calculations()->circle_radius();
  qp.drawEllipse(pos, rad, rad);
}
