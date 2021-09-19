#include "FactoryRes.h"

IContent* FubricRes::create_res(Resources type_res, ICell* cell) const
{
  switch (type_res)
  {
  case Resources::Gold:
    return new class Gold(cell);
  case Resources::Iron:
    return new class Iron(cell);
  case Resources::Stone:
    return new class Stone(cell);
  case Resources::Aluminum:
    return new class Aluminum(cell);
  case Resources::Horses:
    return new class Horses(cell);
  case Resources::Oil:
    return new class Oil(cell);
  case Resources::Uranium:
    return new class Uranium(cell);
  case Resources::Coal:
    return new class Coal(cell);
  case Resources::Fish:
    return new class Fish(cell);
  case Resources::Silver:
    return new class Silver(cell);
  default:
    throw std::runtime_error("This resource doesn't exist");
  }
}
