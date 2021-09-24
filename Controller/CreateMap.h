#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "../IObject.h"
#include "../Graphics/Map.h"

class CreateMap : public IObject
{
public:
  CreateMap(IGameForMap* game_control) :game_control{game_control} {}
  void create_map(Map* map);
  void add_resource(Map* map);

private:
  IGameForMap* game_control;
};

#endif // CREATEMAP_H
