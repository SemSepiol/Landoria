#include "Town.h"

void Town::set_health(int _health)
{
  health = _health;
}

int Town::get_health() const
{
  return health;
}

void Town::set_max_health(int _max_health)
{
    max_health = _max_health;
}

int Town::get_max_health() const
{
  return max_health;
}
