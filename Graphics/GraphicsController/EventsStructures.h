#ifndef EVENTSSTRUCTURES_H
#define EVENTSSTRUCTURES_H

#include <vector>
#include "../../Controllers/Enums.h"
#include "../../IObject.h"

enum Events
{
  Move,
  Build,
  Slip
};

struct Event
{
  Events event;
  virtual Event* copy() const = 0;
  virtual ~Event() {}
protected:
  Event(Events _event) :event{_event} {}
};

struct MoveEvent : Event
{
  size_t cell_move_x;
  size_t cell_move_y;
  virtual Event* copy() const override;
  MoveEvent(size_t _cell_move_x, size_t _cell_move_y)
    : Event{Events::Move}, cell_move_x{_cell_move_x},
      cell_move_y{_cell_move_y} {}
};

struct BuildEvent : Event
{
  Buildings building;
  virtual Event* copy() const override;
  BuildEvent(Buildings _building)
    : Event{Events::Build}, building{_building} {}
};

struct SlipEvent : Event
{
  virtual Event* copy() const override;
  SlipEvent()
    : Event{Events::Slip} {}
};

#endif // EVENTSSTRUCTURES_H
