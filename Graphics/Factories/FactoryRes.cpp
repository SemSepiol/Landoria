#include "FactoryRes.h"

IContent* FactoryRes::create_res(Resources type_res, ICell* cell, int count_of_res) const
{
  switch (type_res)
  {
  case Resources::Gold:
    return new class Gold(cell, count_of_res);
  case Resources::Iron:
    return new class Iron(cell, count_of_res);
  case Resources::Stone:
    return new class Stone(cell, count_of_res);
  case Resources::Aluminum:
    return new class Aluminum(cell, count_of_res);
  case Resources::Horses:
    return new class Horses(cell, count_of_res);
  case Resources::Oil:
    return new class Oil(cell, count_of_res);
  case Resources::Uranium:
    return new class Uranium(cell, count_of_res);
  case Resources::Coal:
    return new class Coal(cell, count_of_res);
  case Resources::Fish:
    return new class Fish(cell, count_of_res);
  case Resources::Silver:
    return new class Silver(cell, count_of_res);
  default:
    throw std::runtime_error("This resource doesn't exist");
  }
}
