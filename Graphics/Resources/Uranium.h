#ifndef URANIUM_H
#define URANIUM_H

#include "Res.h"
#include "../../Controller/Enums.h"

class Uranium : public Res
{
public:
  Uranium(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Uranium; }
  virtual ~Uranium() override {}
};


#endif // URANIUM_H
