#ifndef URANIUM_H
#define URANIUM_H

#include "Res.h"
#include "../../Controllers/Enums.h"


class Uranium : public Res
{
public:
  Uranium(ICell* cell, int count_of_res) : Res{cell, count_of_res}{}
  virtual Resources what_resource_I() const override { return Resources::Uranium; }
  virtual ~Uranium() override {}
};


#endif // URANIUM_H
