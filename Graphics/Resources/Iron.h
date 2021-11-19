#ifndef IRON_H
#define IRON_H

#include "Res.h"
#include "../../Controllers/Enums.h"


class Iron : public Res
{
public:
  Iron(ICell* cell, int count_of_res) : Res{cell, count_of_res}{}
  virtual Resources what_resource_I() const override { return Resources::Iron; }
};

#endif // IRON_H
