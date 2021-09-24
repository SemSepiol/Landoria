#ifndef ALUMINUM_H
#define ALUMINUM_H

#include "Res.h"
#include "../../Controllers/Enums.h"

class Aluminum : public Res
{
public:
  Aluminum(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Aluminum; }
  virtual ~Aluminum() override {}
};

#endif // ALUMINUM_H
