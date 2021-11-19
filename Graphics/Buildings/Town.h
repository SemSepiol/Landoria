#ifndef TOWN_H
#define TOWN_H

#include "Building.h"
#include "../ICell.h"
#include "../../Controllers/Enums.h"


class Town : public Building
{
public:
  Town(ICell* cell) : Building{cell}{}
  virtual Buildings what_building_I() const override { return Buildings::Town; }

  void set_health(int health);
  int get_health() const;
  void set_max_health(int max_health);
  int get_max_health() const;
private:
  int max_health;
  int health;
};

#endif // TOWN_H
