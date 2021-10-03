#ifndef COAL_H
#define COAL_H

#include "Res.h"
#include "../../Controllers/Enums.h"

class Coal : public Res
{
public:
  Coal(ICell* cell, int count_of_res) : Res{cell, count_of_res}{}
  virtual Resources what_resource_I() const override { return Resources::Coal; }
  virtual ~Coal() override {}
};

#endif // COAL_H
