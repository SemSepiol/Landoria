#ifndef HORSES_H
#define HORSES_H

#include "Res.h"
#include "../../Controller/Enums.h"

class Horses : public Res
{
public:
  Horses(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Horses; }
  virtual ~Horses() override {}
};

#endif // HORSES_H
