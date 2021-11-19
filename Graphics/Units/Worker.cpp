#include "Worker.h"

void Worker::set_standard_charaterichtics()
{
  Unit::set_standard_charaterichtics();

  build_speed = UnitsCharaterichtics().get_worker_build_speed();
}

void Worker::set_build_speed(int _build_speed)
{
  build_speed = _build_speed;
}

int Worker::get_build_speed() const
{
  return build_speed;
}
