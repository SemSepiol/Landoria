#ifndef EVENTSSTRUCTURES_H
#define EVENTSSTRUCTURES_H

#include <vector>
#include "../../Controllers/Enums.h"
#include "../../IObject.h"

enum Events
{
  Move,
  Build,
  Slip,
  Demolish
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
  Position cell_move;
  virtual Event* copy() const override;
  MoveEvent(Position _cell_move)
    : Event{Events::Move}, cell_move{_cell_move} {}
};

struct BuildEvent : Event
{
  Buildings building;
  Position pos_cell;
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

struct DemolishEvent : Event
{
  virtual Event* copy() const override;
  DemolishEvent()
    : Event{Events::Demolish} {}
};

#endif // EVENTSSTRUCTURES_H
