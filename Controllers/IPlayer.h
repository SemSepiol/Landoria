#ifndef IPLAYER_H
#define IPLAYER_H

#include "IObject.h"
#include "../Graphics/Units/Unit.h"
#include "../Graphics/GraphicsController/EventsStructures.h"

class IPlayer : public IObject
{
public:
  virtual void click_unit(class Unit* unit) = 0;
  virtual void set_initial_units(size_t initial_cell_x, size_t initial_cell_y) = 0;
  virtual void menu_event(class Unit* unit, Event* event) = 0;
};


#endif // IPLAYER_H
