#include "FactoryContents.h"

std::vector<std::unique_ptr<IContent>> FactoryContents::contents() const
{
  std::vector<std::unique_ptr<IContent>> cont;
  for(int i{0}; i < 6; ++i){
    IContent* c = new class Worker(cell);
    cont.push_back(std::unique_ptr<IContent>(c));
  }
  return cont;
}
