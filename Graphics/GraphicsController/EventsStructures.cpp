#include "EventsStructures.h"

Event* MoveEvent::copy() const
{
  return new MoveEvent{cell_move};
}

Event* BuildEvent::copy() const
{
  return new BuildEvent{building};
}

Event* SlipEvent::copy() const
{
  return new SlipEvent{};
}

Event* DemolishEvent::copy() const
{
  return new DemolishEvent{};
}

