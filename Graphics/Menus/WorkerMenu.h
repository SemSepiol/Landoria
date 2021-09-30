#ifndef WORKERMENU_H
#define WORKERMENU_H

#include <QPoint>

#include "AMenuForUnit.h"
#include "../GraphicsController/EventsStructures.h"

class WorkerMenu : public AMenuForUnit
{
  const int _count_button = 1;
public:
  WorkerMenu(QWidget* win, IPlayerForMenu* player, class Unit* unit);
  virtual int count_button() const override;

protected:
  virtual Event* what_butt(int num_butt) override;
};

#endif // WORKERMENU_H
