#ifndef IOBJECT_H
#define IOBJECT_H

#include <utility>

struct Position
{
  size_t x;
  size_t y;
  Position(size_t _x, size_t _y)
    :x{_x}, y{_y} {}
  Position()
    :x{0}, y{0} {}
  Position(std::pair<size_t, size_t> pos)
    :x{pos.first}, y{pos.second}
  {}

  bool operator==(Position other)
  { return x == other.x and y == other.y; }

  bool operator!=(Position other)
  { return x != other.x or y != other.y; }
};

class IObject
{
public:
  virtual ~IObject(){}
protected:
  IObject(){}
};



#endif // IOBJECT_H
