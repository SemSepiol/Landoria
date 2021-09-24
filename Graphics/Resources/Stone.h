#ifndef STONE_H
#define STONE_H

#include "Res.h"
#include "../../Controllers/Enums.h"

class Stone : public Res
{
public:
  Stone(ICell* cell) : Res{cell}{}

  virtual Resources what_resource_I() const override { return Resources::Stone; }
};

#endif // STONE_H
