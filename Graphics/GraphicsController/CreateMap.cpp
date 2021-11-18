#include "CreateMap.h"
#include <stdlib.h>

void CreateMap::create_map(Map* map)
{
  int choice = rand() % 2;
  switch (choice)
  {
  case 0:
       for(size_t i{0}; i < game_control->count_cell_x(); ++i)
           for(int j{0}; j < 4; ++j)
           {
                 ControlContents controlcontents{map->cell_by_indexes({i, game_control->count_cell_y() / 2 - 3 + j})};
                 controlcontents.set_main_landscape(MainLandscapes(7));
           }
  case 1:
      for(size_t i{1}; i < 4; ++i)
          for(size_t j{0}; j < game_control->count_cell_y(); ++j)
          {
               ControlContents controlcontents{map->cell_by_indexes({game_control->count_cell_x()/2 + i, j})};
               controlcontents.set_main_landscape(MainLandscapes(7));
          }
      for(size_t j{2}; j < game_control->count_cell_y() - 2; ++j)
      {
          ControlContents controlcontents{map->cell_by_indexes({game_control->count_cell_x()/2, j})};
          controlcontents.set_main_landscape(MainLandscapes(5));
      }

       for(size_t i{1}; i < game_control->count_cell_x()/2; ++i)
       {
           ControlContents controlcontents{map->cell_by_indexes({i, 1})};
           controlcontents.set_main_landscape(MainLandscapes(5));
       }
       for(size_t j{1}; j < game_control->count_cell_y() - 2; ++j)
       {
           ControlContents controlcontents{map->cell_by_indexes({1, j})};
           controlcontents.set_main_landscape(MainLandscapes(5));
       }
       for(size_t i{1}; i < game_control->count_cell_x()/2 + 1; ++i)
       {
           ControlContents controlcontents{map->cell_by_indexes({i, game_control->count_cell_y() - 2})};
           controlcontents.set_main_landscape(MainLandscapes(5));
       }
       for(size_t j{2}; j < game_control->count_cell_y() - 2; ++j)
       {
            ControlContents controlcontents{map->cell_by_indexes({game_control->count_cell_x()/2 + 3, j})};
            controlcontents.set_main_landscape(MainLandscapes(5));
       }
       for(size_t i{game_control->count_cell_x()/2 + 4}; i < game_control->count_cell_x() - 2; ++i)
       {
           ControlContents controlcontents{map->cell_by_indexes({i, game_control->count_cell_y() - 2})};
           controlcontents.set_main_landscape(MainLandscapes(5));
       }
       for(size_t i{game_control->count_cell_x()/2 + 3}; i < game_control->count_cell_x() - 2; ++i)
       {
           ControlContents controlcontents{map->cell_by_indexes({i, 1})};
           controlcontents.set_main_landscape(MainLandscapes(5));
       }
       for(size_t j{2}; j < game_control->count_cell_y() - 1; ++j)
       {
            ControlContents controlcontents{map->cell_by_indexes({game_control->count_cell_x() - 2, j})};
            controlcontents.set_main_landscape(MainLandscapes(5));
       }
  }
  for(size_t i{0}; i < game_control->count_cell_x(); ++i)
    for(size_t j{0}; j < 2; ++j)
  {
      ControlContents controlcontents{map->cell_by_indexes({i, j})};
      if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
  }
  for(size_t i{0}; i < 2; ++i)
    for(size_t j{0}; j < game_control->count_cell_y(); ++j)
  {
      ControlContents controlcontents{map->cell_by_indexes({i, j})};
      if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
  }
  for(size_t i{game_control->count_cell_x() - 2}; i < game_control->count_cell_x(); ++i)
    for(size_t j{0}; j < game_control->count_cell_y(); ++j)
  {
      ControlContents controlcontents{map->cell_by_indexes({i, j})};
      if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
  }
  for(size_t i{0}; i < game_control->count_cell_x(); ++i)
    for(size_t j{game_control->count_cell_y() - 2}; j < game_control->count_cell_y(); ++j)
  {
      ControlContents controlcontents{map->cell_by_indexes({i, j})};
      if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
  }

 for(int i{0}; i < game_control->count_cell_x(); ++i)
    for(int j{2}; j < 4; ++j)
    {

      ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
 int map_size_y = game_control->count_cell_y();
 for(int i{0}; i < game_control->count_cell_x(); ++i)
    for(int j{map_size_y - 4}; j < game_control->count_cell_y(); ++j)
    {

      ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
 for(int i{2}; i < 3; ++i)
    for(int j{0}; j < game_control->count_cell_y(); ++j)
    {

      ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
 for(int i{0}; i < game_control->count_cell_y(); ++i)
    {

      ControlContents controlcontents{map->cell_by_indexes({game_control->count_cell_x() / 2 - 1, size_t(i)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
 for(int i{0}; i < game_control->count_cell_y(); ++i)
    {

      ControlContents controlcontents{map->cell_by_indexes({game_control->count_cell_x() - 3, size_t(i)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
 for(int i{0}; i < game_control->count_cell_y(); ++i)
    {

      ControlContents controlcontents{map->cell_by_indexes({game_control->count_cell_x() / 2 + 4, size_t(i)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }

for(int i{0}; i < game_control->count_cell_x(); ++i)
   for(int j{0}; j < game_control->count_cell_y(); ++j)
   {

     ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
     if(!controlcontents.has_main_landscape())
       controlcontents.set_main_landscape(MainLandscapes(rand() % 5));
   }
}

void CreateMap::add_resource(Map* map)
{
  for(int i{0}; i < game_control->count_cell_x(); ++i)
    for(int j{0}; j < game_control->count_cell_y(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
      controlcontents.add_resource(Resources(rand() % 10), rand() % 10);
    }
}
