#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "../Cell.h"
#include "../Map.h"
#include "../../IObject.h"


class CreateMap : public IObject
{
public:
  CreateMap(IMapGraphicsController* _graphics_controller)
    :graphics_controller{_graphics_controller} {}
  void create_map(Map* map);
  void add_resource(Map* map);

  Position initial_pos_player(int num_player);
private:
  Resources give_resourse(int number);
  IMapGraphicsController* graphics_controller;
};

#endif // CREATEMAP_H
