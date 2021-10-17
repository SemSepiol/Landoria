#ifndef PLAYERTOWN_H
#define PLAYERTOWN_H

#include <memory>

#include "../../IObject.h"
#include "../../Graphics/Buildings/Town.h"
#include "../TownBuildings.h"

class PlayerTown : public IObject
{
public:
  PlayerTown(class Town* town, Position position_town);

  Position position_town() const;
  class Town* town() const;

  size_t count_town_buildings() const;
  TownBuildings get_town_building(size_t ind) const;
  void add_town_building(TownBuildings town_building);
private:
  std::unique_ptr<class Town> _town;
  Position _pos;

  std::vector<TownBuildings> buildings;
};

#endif // PLAYERTOWN_H
