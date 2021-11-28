#ifndef FACTORYCOLOR_H
#define FACTORYCOLOR_H

#include <map>

#include <QColor>

#include "../../Controllers/Enums.h"
#include "../../IObject.h"


class FactoryColor : public IObject
{
  std::map<Countries, QColor> _country_color{
    {Countries::Nothing, Qt::red},
    {Countries::Russia, Qt::yellow},
    {Countries::America, Qt::blue}
  };

public:
  QColor country_color(Countries country) const;
};

#endif // FACTORYCOLOR_H
