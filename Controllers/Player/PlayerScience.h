#ifndef PLAYERSCIENCE_H
#define PLAYERSCIENCE_H

#include "../../IObject.h"
#include "../TownBuildings.h"
#include "../Enums.h"

class PlayerScience : public IObject
{
public:
  PlayerScience();
  size_t count_open_town_buildings() const;
  TownBuildings get_open_town_building(size_t ind) const;

  size_t count_open_units() const;
  Units get_open_unit(size_t ind) const;

  size_t count_best_open_units() const;
  Units get_best_open_unit(size_t ind) const;
};

#endif // PLAYERSCIENCE_H
