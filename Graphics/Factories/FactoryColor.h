#ifndef FACTORYCOLOR_H
#define FACTORYCOLOR_H

#include <map>

#include <QColor>

#include "../../Controllers/Enums.h"
#include "../../IObject.h"


class FactoryColor : public IObject
{
public:
  QColor country_color(Countries country) const;
};

#endif // FACTORYCOLOR_H
