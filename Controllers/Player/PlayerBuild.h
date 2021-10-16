#ifndef PLAYERBUILD_H
#define PLAYERBUILD_H

#include "PlayerUnit.h"
#include "../../Graphics/Buildings/Building.h"

struct PlayerBuild
{
  PlayerUnit* unit;
  class Building* building;

  PlayerBuild(PlayerUnit* _unit, class Building* _building)
    :unit{_unit}, building{_building}
  {}
};

#endif // PLAYERBUILD_H
