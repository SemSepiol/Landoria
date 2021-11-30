#ifndef CITIZENMENU_H
#define CITIZENMENU_H

#include "AMenuForUnit.h"
#include "../../GraphicsController/EventsStructures.h"
#include "../../Map/Cell.h"


class CitizenMenu : public AMenuForUnit
{
public:
  CitizenMenu(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
              PlayerUnit* unit, Cell* cell);
private:
  void set_buttons();
  void set_is_enable(MyButton& my_butt);
};

#endif // CITIZENMENU_H
