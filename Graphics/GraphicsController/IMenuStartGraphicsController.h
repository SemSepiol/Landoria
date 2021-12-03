#ifndef IMENUSTARTGRAPHICSCONTROLLER_H
#define IMENUSTARTGRAPHICSCONTROLLER_H

#include <QWidget>

#include "../../IObject.h"


class IMenuStartGraphicsController : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual void start_game() = 0;
};

#endif // IMENUSTARTGRAPHICSCONTROLLER_H
