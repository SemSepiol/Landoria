#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "../../IObject.h"
#include "../Map.h"
#include "../Cell.h"

class CreateMap : public IObject
{
public:
  CreateMap(IGraphicsControllerForMap* game_control) :game_control{game_control} {}
  void create_map(Map* map);
  void add_resource(Map* map);

private:
  IGraphicsControllerForMap* game_control;
};

#endif // CREATEMAP_H
