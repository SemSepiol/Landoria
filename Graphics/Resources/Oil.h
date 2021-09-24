#ifndef OIL_H
#define OIL_H

#include "Res.h"
#include "../../Controllers/Enums.h"

class Oil : public Res
{
public:
  Oil(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Oil; }
  virtual ~Oil() override {}
};

#endif // OIL_H
