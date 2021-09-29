#include "CreateMap.h"

void CreateMap::create_map(Map* map)
{
  for(int i{0}; i < game_control->count_cell_x(); ++i)
    for(int j{0}; j < game_control->count_cell_y(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes(size_t(i), size_t(j))};
//      controlcontents.set_main_landscape(MainLandscapes::Plain);
      controlcontents.set_main_landscape(MainLandscapes(rand() % 8));
//      controlcontents.set_other_landscape(OtherLandscapes(rand() % 5));
    }
}

void CreateMap::add_resource(Map* map)
{
  for(int i{0}; i < game_control->count_cell_x(); ++i)
    for(int j{0}; j < game_control->count_cell_y(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes(size_t(i), size_t(j))};
      controlcontents.add_resource(Resources(rand() % 10));
    }
}
