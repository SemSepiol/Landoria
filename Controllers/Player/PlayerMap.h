#ifndef PLAYERMAP_H
#define PLAYERMAP_H

#include <vector>

#include "../Enums.h"
#include "../../Graphics/Map/ICell.h"
#include "../../IObject.h"


class PlayerMap : public IObject
{
public:
  PlayerMap(Position count_cell, Mod mod);
  ICell::ShowCell get_show_cell(Position pos_cell) const;
  void set_show_cell(Position pos_cell);
  void set_notvisible_cell(Position pos_cell);

private:
  std::vector<std::vector<ICell::ShowCell>> map;
  Mod mod;
};

#endif // PLAYERMAP_H
