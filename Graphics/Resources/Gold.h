#ifndef GOLD_H
#define GOLD_H

#include "Res.h"
#include "../../Controllers/Enums.h"

class Gold : public Res
{
public:
  Gold(ICell* cell, int count_of_res) : Res{cell, count_of_res}{}
  virtual Resources what_resource_I() const override { return Resources::Gold; }
  virtual ~Gold() override {}
};

#endif // GOLD_H
