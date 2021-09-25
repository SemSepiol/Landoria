#ifndef EVENTSSTRUCTURES_H
#define EVENTSSTRUCTURES_H

#include <vector>
#include "../../Controllers/Enums.h"
#include "../Cell.h"

enum Events
{
  Move,
  Build
};

struct Event
{
  Events event;

protected:
  Event(Events _event) :event{_event} {}
};

struct Move : Event
{
  size_t cell_move_x;
  size_t cell_move_y;
  Cell* move_cell;
  Move(size_t _cell_move_x, size_t _cell_move_y, Cell* _move_cell)
    : Event{Events::Move}, cell_move_x{_cell_move_x},
      cell_move_y{_cell_move_y}, move_cell{_move_cell} {}
};

struct Build : Event
{
  Buildings building;

  Build(Buildings _building)
    : Event{Events::Build}, building{_building} {}
};

#endif // EVENTSSTRUCTURES_H
