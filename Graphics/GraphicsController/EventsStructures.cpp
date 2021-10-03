#include "EventsStructures.h"

Event* Move_event::copy() const
{
  return new Move_event{cell_move_x, cell_move_y};
}

Event* Build_event::copy() const
{
  return new Build_event{building};
}

Event* Slip_event::copy() const
{
  return new Slip_event{};
}
