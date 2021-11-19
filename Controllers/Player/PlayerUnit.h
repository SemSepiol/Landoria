#ifndef PLAYERUNIT_H
#define PLAYERUNIT_H

#include <memory>

#include "../../Graphics/GraphicsController/EventsStructures.h"
#include "../../IObject.h"


struct PlayerUnit
{
  Position pos;
  class Unit* unit;
  std::unique_ptr<Event> event;

  PlayerUnit(class Unit* _unit, Position _pos)
    :pos{_pos}, unit{_unit}, event{new struct NoEvent} {}

  PlayerUnit(const PlayerUnit& playerunit)
    :pos{playerunit.pos}, unit{playerunit.unit}, event{playerunit.event->copy()} {}
};

#endif // PLAYERUNIT_H
