#ifndef CITIZENMENU_H
#define CITIZENMENU_H

#include "AMenuForUnit.h"
#include "../GraphicsController/EventsStructures.h"

class CitizenMenu : public AMenuForUnit
{
  const int _count_button = 3;
public:
  CitizenMenu(QWidget* win, IPlayerForMenu* player, class Unit* unit);
  virtual int count_button() const override;

protected:
  virtual Event* what_butt(int num_butt) override;
};

#endif // CITIZENMENU_H
