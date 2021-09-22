#include "FactoryBuild.h"


IContent* FubricBuild::create_building(Buildings type_build, ICell *cell) const
{
    switch (type_build)
    {
    case Buildings::Town:
        return new class Town(cell);
    case Buildings::Farm:
        return new class Farm(cell);
    case Buildings::FishingBoats:
        return new class FishingBoats(cell);
    case Buildings::Fort:
        return new class Fort(cell);
    case Buildings::LumberMill:
        return new class LumberMill(cell);
    case Buildings::Mine:
        return new class Mine(cell);
    case Buildings::OilWell:
        return new class OilWell(cell);
    case Buildings::Pasture:
        return new class Pasture(cell);
    case Buildings::Quarry:
        return new class Quarry(cell);
    case Buildings::TradingPost:
        return new class TradingPost(cell);
    default:
        throw std::runtime_error("This build doesn't exist");
    }
}
