#ifndef COAL_H
#define COAL_H

#include "Res.h"
#include "../../Controller/Enums.h"

class Coal : public Res
{
public:
  Coal(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Coal; }
  virtual ~Coal() override {}
};

#endif // COAL_H
