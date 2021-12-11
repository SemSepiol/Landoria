#ifndef PLAYERBUILD_H
#define PLAYERBUILD_H

#include "PlayerUnit.h"
#include "../../Graphics/Buildings/Building.h"


struct PlayerBuild
{
  PlayerUnit* unit;
  class Building* building;
  Position pos;

  PlayerBuild(PlayerUnit* _unit, class Building* _building, Position _pos)
    :unit{_unit}, building{_building}, pos{_pos}
  {}
};

#endif // PLAYERBUILD_H
