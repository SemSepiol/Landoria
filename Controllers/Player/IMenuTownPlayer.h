#ifndef IMENUTOWNPLAYER_H
#define IMENUTOWNPLAYER_H

#include "IObject.h"
#include "PlayerScience.h"

class IMenuTownPlayer : public IObject
{
public:
  virtual PlayerScience* player_science() const = 0;
};

#endif // IMENUTOWNPLAYER_H
