#ifndef IPLAYER_H
#define IPLAYER_H

#include "IObject.h"
#include "../../Graphics/GraphicsController/EventsStructures.h"
#include "../../Graphics/Units/Unit.h"


class IPlayer : public IObject
{
public:
  virtual void click_unit(class Unit* unit) = 0;
  virtual void click_town(class Town* town) = 0;
  virtual void del_menu_town() = 0;
  virtual void set_initial_units(Position initial_cell) = 0;
  virtual void menu_event(class Unit* unit, Event* event) = 0;
};

#endif // IPLAYER_H
