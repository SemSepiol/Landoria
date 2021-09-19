#ifndef FISH_H
#define FISH_H

#include "Res.h"
#include "../../Controller/Enums.h"

class Fish : public Res
{
public:
  Fish(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Fish; }
  virtual ~Fish() override {}
};

#endif // FISH_H
