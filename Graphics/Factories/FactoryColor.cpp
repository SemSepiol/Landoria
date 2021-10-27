#include "FactoryColor.h"

QColor FactoryColor::country_color(Countries country) const
{
  return _country_color.at(country);
}
