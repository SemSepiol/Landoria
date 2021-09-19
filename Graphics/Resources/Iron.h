#ifndef IRON_H
#define IRON_H

#include "Res.h"
#include "../../Controller/Enums.h"

class Iron : public Res
{
public:
  Iron(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Iron; }
};

#endif // IRON_H
