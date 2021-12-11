#include "FactoryColor.h"

QColor FactoryColor::country_color(Countries country) const
{
  std::map<Countries, QColor> _country_color{
    {Countries::Nothing, Qt::red},
    {Countries::Russia, Qt::yellow},
    {Countries::America, Qt::blue},
    {Countries::China, Qt::green},
    {Countries::England, Qt::magenta}
  };

  return _country_color.at(country);
}
