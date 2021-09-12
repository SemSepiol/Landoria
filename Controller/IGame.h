#ifndef IGAME_H
#define IGAME_H

#include <QWidget>

#include "../IObject.h"

class IGame : public IObject
{
public:
  virtual QWidget* window() = 0;
protected:
  IGame(){}


};

#endif // IGAME_H
