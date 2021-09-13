#ifndef FACTORYCONTENTS_H
#define FACTORYCONTENTS_H

#include "../IObject.h"
#include "../Graphics/ICell.h"
#include "../Graphics/Units/Worker.h"

class FactoryContents : public IObject
{
public:
  FactoryContents(ICell* cell) : cell{cell}{}

  std::vector<std::unique_ptr<IContent>> contents() const;

  virtual ~FactoryContents() {}
private:
  ICell* cell;
};


#endif // FACTORYCONTENTS_H
