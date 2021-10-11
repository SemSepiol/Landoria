#include "PlayerTown.h"

PlayerTown::PlayerTown(class Town* town, Position pos)
  :_town{town}, _pos{pos}
{}

Position PlayerTown::position_town() const
{
  return _pos;
}

class Town* PlayerTown::town() const
{
  return _town.get();
}
