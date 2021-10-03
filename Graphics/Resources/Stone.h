#ifndef STONE_H
#define STONE_H

#include "Res.h"
#include "../../Controllers/Enums.h"

class Stone : public Res
{
public:
  Stone(ICell* cell, int count_of_res) : Res{cell, count_of_res}{}

  virtual Resources what_resource_I() const override { return Resources::Stone; }
};

#endif // STONE_H
