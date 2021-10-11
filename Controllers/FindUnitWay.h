#ifndef FINDUNITWAY_H
#define FINDUNITWAY_H

#include <vector>

#include "../IObject.h"
#include "../Graphics/Units/Unit.h"
#include "../Graphics/IMap.h"

struct OneMove
{
  Position start;
  Position end;
  int spent_movement_points;

  /*
   * массив который хранит подперемещения в одном перемещении
   * первый элемент равняется start
   * последний элемент равняется end
  */
  std::vector<Position> minimove;

  OneMove(Position _start, Position _end,
          int _spent_movement_points, std::vector<Position> _minimove)
    :start{_start}, end{_end}, spent_movement_points{_spent_movement_points},
      minimove{_minimove}
  {}
  OneMove(Position _start)
    :start{_start} {minimove.push_back(start);}

  void add_move(Position pos);
};

class Way : public IObject
{
  std::vector<OneMove> way;
public:
  /// number_move с нуля
  OneMove get_move_in_way(size_t number_move) const;
  size_t get_count_moves_in_way() const;
  void add_move(OneMove move);
};

class FindUnitWay : public IObject
{
public:
  Way get_way(class Unit* unit, IMapForFind* map, Position start, Position end);
  OneMove get_first_move(class Unit* unit, IMapForFind* map, Position start, Position end);
};

#endif // FINDUNITWAY_H
