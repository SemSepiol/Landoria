#ifndef FISH_H
#define FISH_H

#include "Res.h"
#include "../../Controllers/Enums.h"


class Fish : public Res
{
public:
  Fish(ICell* cell, int count_of_res) : Res{cell, count_of_res}{}
  virtual Resources what_resource_I() const override { return Resources::Fish; }
  virtual ~Fish() override {}
};

#endif // FISH_H
