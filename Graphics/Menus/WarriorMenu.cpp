#include "WarriorMenu.h"

WarriorMenu::WarriorMenu(QWidget* _win, IUnitMenuGraphicsController* _graphics_controller,
                         class Unit* _unit, Cell* _cell)
  :AMenuForUnit(_win, _graphics_controller, _unit, _cell)
{ set_buttons(); }

void WarriorMenu::set_buttons()
{
  buttons.push_back(new MoveEvent{{0,0}});
  buttons.push_back(new SlipEvent{});
}

void WarriorMenu::set_is_enable(MyButton& )
{

}
