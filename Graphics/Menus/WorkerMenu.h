#ifndef WORKERMENU_H
#define WORKERMENU_H

#include <QPoint>

#include "AMenuForUnit.h"
#include "../GraphicsController/EventsStructures.h"
#include "../Cell.h"

class WorkerMenu : public AMenuForUnit
{
public:
  WorkerMenu(QWidget* win, IGraphicsControllerMenuForUnit* graphics_controller,
             class Unit* unit, Cell* cell);
};

#endif // WORKERMENU_H
