#ifndef WARRIORMENU_H
#define WARRIORMENU_H

#include "AMenuForUnit.h"
#include "../../GraphicsController/EventsStructures.h"
#include "../../Map/Cell.h"


class WarriorMenu : public AMenuForUnit
{
public:
  WarriorMenu(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
              PlayerUnit* unit, Cell* cell);
private:
  void set_buttons() override;
  void set_is_enable(MyButton& my_butt);
};

#endif // WARRIORMENU_H
