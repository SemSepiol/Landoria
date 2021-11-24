#include "CitizenMenu.h"
#include <iostream>

CitizenMenu::CitizenMenu(QWidget* _win, IUnitMenuGraphicsController* _graphics_controller,
                         PlayerUnit* _unit, Cell* _cell)
  :AMenuForUnit(_win, _graphics_controller, _unit, _cell)
{ set_buttons(); }

void CitizenMenu::set_buttons()
{
  AMenuForUnit::set_buttons();
  buttons.push_back(new BuildEvent{Buildings::Town});
  set_is_enable(buttons[0]);
  buttons.push_back(new MoveEvent{{0,0}});
  buttons.push_back(new SlipEvent{});
}

void CitizenMenu::set_is_enable(MyButton& my_butt)
{
  if(my_butt.event->event == Events::Build)
  {
    ControlContents controlcontents(cell);
    if(controlcontents.has_building())
      if(controlcontents.get_building()->what_building_I() == Buildings::Town)
        my_butt.is_enable = false;
  }

  if(my_butt.event->event == Events::Slip)
  {
    ControlContents controlcontents(cell);
    int count = 0;
    for(auto type_unit : controlcontents.get_units())
      if(type_unit == Units::Worker || type_unit == Units::Citizen)
        count++;
    if(count > 1)
      my_butt.is_enable = false;
  }
}
