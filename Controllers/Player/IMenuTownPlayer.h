#ifndef IMENUTOWNPLAYER_H
#define IMENUTOWNPLAYER_H

#include "IObject.h"
#include "PlayerRes.h"
#include "PlayerScience.h"


class IMenuTownPlayer : public IObject
{
public:
  virtual PlayerScience* player_science() const = 0;

  virtual int get_gold_per_turn() const = 0;
  virtual int get_science_per_turn() const = 0;
  virtual PlayerRes* get_player_res() const = 0;
};

#endif // IMENUTOWNPLAYER_H
