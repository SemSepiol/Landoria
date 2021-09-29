#ifndef EVENTSSTRUCTURES_H
#define EVENTSSTRUCTURES_H

#include <vector>
#include "../../Controllers/Enums.h"

enum Events
{
  Move,
  Build,
  Slip
};

struct Event
{
  Events event;

protected:
  Event(Events _event) :event{_event} {}
};

struct Move_event : Event
{
  size_t cell_move_x;
  size_t cell_move_y;
  Move_event(size_t _cell_move_x, size_t _cell_move_y)
    : Event{Events::Move}, cell_move_x{_cell_move_x},
      cell_move_y{_cell_move_y} {}
};

struct Build_event : Event
{
  Buildings building;

  Build_event(Buildings _building)
    : Event{Events::Build}, building{_building} {}
};

struct Slip_event : Event
{
  Slip_event()
    : Event{Events::Slip} {}
};

#endif // EVENTSSTRUCTURES_H
