#ifndef CITIZENMENU_H
#define CITIZENMENU_H

#include <vector>

#include "AMenuForUnit.h"
#include "../GraphicsController/EventsStructures.h"
#include "../Cell.h"

class CitizenMenu : public AMenuForUnit
{
public:
  CitizenMenu(QWidget* win, IGraphicsControllerMenuForUnit* graphics_controller,
              class Unit* unit, Cell* cell);
};

#endif // CITIZENMENU_H
