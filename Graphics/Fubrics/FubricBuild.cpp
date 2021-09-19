#include "FubricBuild.h"


IContent* FubricBuild::CreateBuilding(Buildings type_build, ICell *cell) const
{
    switch (type_build)
    {
    case Buildings::Town:
        return new class Town(cell);

    default:
        throw std::runtime_error("This unit doesn't exist");
    }
}
