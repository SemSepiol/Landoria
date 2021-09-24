#ifndef SILVER_H
#define SILVER_H

#include "Res.h"
#include "../../Controllers/Enums.h"

class Silver : public Res
{
public:
  Silver(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Silver; }
  virtual ~Silver() override {}
};

#endif // SILVER_H
