#ifndef TOWNBUILDNEEDS_H
#define TOWNBUILDNEEDS_H

#include "../IObject.h"
#include "TownBuildings.h"
#include "Enums.h"

class TownBuildNeeds : public IObject
{
public:
 int get_build_need_production(TownBuildings type_building) const;
 int get_build_need_production(Units unit) const;
};

#endif // TOWNBUILDNEEDS_H
