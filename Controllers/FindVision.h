#ifndef FINDUNITVISION_H
#define FINDUNITVISION_H

#include <queue>
#include <vector>

#include "Player/PlayerTown.h"
#include "../IObject.h"
#include "../Graphics/Map/IMap.h"
#include "../Graphics/Units/Unit.h"


class FindVision : public IObject
{
public:
  std::vector<Position> unit_vision(class Unit* unit, Position pos_unit, IMapForFind* map) const;
  std::vector<Position> town_vision(PlayerTown* town, IMapForFind* map) const;
};

#endif // FINDUNITVISION_H
