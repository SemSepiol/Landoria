#ifndef WARRIORMENU_H
#define WARRIORMENU_H

#include "AMenuForUnit.h"
#include "../GraphicsController/EventsStructures.h"
#include "../Cell.h"

class WarriorMenu : public AMenuForUnit
{
public:
  WarriorMenu(QWidget* win, IGraphicsControllerMenuForUnit* graphics_controller,
              class Unit* unit, Cell* cell);
private:
  void set_buttons();
  void set_is_enable(MyButton& my_butt);
};

#endif // WARRIORMENU_H
