#ifndef FINDUNITVISION_H
#define FINDUNITVISION_H

#include <vector>
#include <queue>

#include "../IObject.h"
#include "../Graphics/Units/Unit.h"
#include "../Graphics/IMap.h"

class FindUnitVision : public IObject
{
public:
  std::vector<Position> unit_vision(class Unit* unit, Position pos_unit, IMapForFind* map) const;
};

#endif // FINDUNITVISION_H
