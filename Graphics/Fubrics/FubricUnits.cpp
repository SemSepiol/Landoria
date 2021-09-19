#include "FubricUnits.h"


IContent* FubricUnits::CreateUnit(Units type_unit, ICell *cell) const
{
    switch (type_unit)
    {
    case Units::Worker:
        return new class Worker(cell);
    case Units::Citizen:
        return new class Citizen(cell);
    default:
        throw std::runtime_error("This unit doesn't exist");
    }
}
