#include "FactoryUnits.h"


IContent* FactoryUnits::create_unit(Units type_unit, ICell *cell) const
{
    switch (type_unit)
    {
    case Units::Worker:
      return new class Worker(cell);
    case Units::Citizen:
      return new class Citizen(cell);
    case Units::Bowman:
      return new class Bowman(cell);
    case Units::Swordsman:
      return new class Swordsman(cell);
    default:
        throw std::runtime_error("This unit doesn't exist");
    }
}
