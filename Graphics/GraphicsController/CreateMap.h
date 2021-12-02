#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "../Map/Cell.h"
#include "../Map/Map.h"
#include "../../IObject.h"


class CreateMap : public IObject
{
public:
  CreateMap(IMapGraphicsController* _graphics_controller)
    :graphics_controller{_graphics_controller} {}

  void create_map(Map* map);
  void add_resource(Map* map);

  std::vector<Position> initial_pos_player(int num_player, Map* map);
private:
  Resources give_resourse(int number);

  void set_landscapes(Map* map);
  void set_otherlandscapes(Map* map);

  IMapGraphicsController* graphics_controller;
};

#endif // CREATEMAP_H
