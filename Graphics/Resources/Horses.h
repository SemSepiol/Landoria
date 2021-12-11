#ifndef HORSES_H
#define HORSES_H

#include "Res.h"
#include "../../Controllers/Enums.h"


class Horses : public Res
{
public:
  Horses(ICell* cell, int count_of_res) : Res{cell, count_of_res}{}
  virtual Resources what_resource_I() const override { return Resources::Horses; }
  virtual ~Horses() override {}
};

#endif // HORSES_H
