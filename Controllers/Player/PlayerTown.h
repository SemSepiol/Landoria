#ifndef PLAYERTOWN_H
#define PLAYERTOWN_H

#include <memory>

#include "../../IObject.h"
#include "../../Graphics/Buildings/Town.h"

class PlayerTown : public IObject
{
public:
  PlayerTown(class Town* town, Position position_town);

  Position position_town() const;
  class Town* town() const;
private:
  std::unique_ptr<class Town> _town;
  Position _pos;
};

#endif // PLAYERTOWN_H
