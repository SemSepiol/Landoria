#ifndef GOLD_H
#define GOLD_H

#include "Res.h"
#include "../../Controller/Enums.h"

class Gold : public Res
{
public:
  Gold(ICell* cell) : Res{cell}{}
  virtual Resources what_resource_I() const override { return Resources::Gold; }
  virtual ~Gold() override {}
};

#endif // GOLD_H
