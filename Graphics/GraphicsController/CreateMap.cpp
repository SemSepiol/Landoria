#include "CreateMap.h"

void CreateMap::create_map(Map* map)
{
  for(size_t i{0}; i < game_control->count_cell_x(); ++i)
    for(size_t j{0}; j < game_control->count_cell_y(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({i, j})};
//      controlcontents.set_main_landscape(MainLandscapes::Mountain);
      controlcontents.set_main_landscape(MainLandscapes(rand() % 8));
//      controlcontents.set_other_landscape(OtherLandscapes(rand() % 6));
    }
}

void CreateMap::add_resource(Map* map)
{
  for(size_t i{0}; i < game_control->count_cell_x(); ++i)
    for(size_t j{0}; j < game_control->count_cell_y(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({i, j})};
      controlcontents.add_resource(Resources(rand() % 10), rand()%10);
    }
}
