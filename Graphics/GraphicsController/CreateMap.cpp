#include "CreateMap.h"
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <ctime>


void CreateMap::create_map(Map* map)
{
  set_landscapes(map);
  set_otherlandscapes(map);
}

void CreateMap::set_landscapes(Map* map)
{
    for(size_t i{1}; i < 4; ++i)
      for(size_t j{0}; j < graphics_controller->count_cell_y(); ++j)
      {
        ControlContents controlcontents{map->cell_by_indexes({graphics_controller->count_cell_x()/2 + i, j})};
        controlcontents.set_main_landscape(MainLandscapes(7));
      }
    for(size_t j{2}; j < graphics_controller->count_cell_y() - 2; ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({graphics_controller->count_cell_x()/2, j})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }

    for(size_t i{1}; i < graphics_controller->count_cell_x()/2; ++i)
    {
      ControlContents controlcontents{map->cell_by_indexes({i, 1})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }
    for(size_t j{1}; j < graphics_controller->count_cell_y() - 2; ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({1, j})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }
    for(size_t i{1}; i < graphics_controller->count_cell_x()/2 + 1; ++i)
    {
      ControlContents controlcontents{map->cell_by_indexes({i, graphics_controller->count_cell_y() - 2})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }
    for(size_t j{2}; j < graphics_controller->count_cell_y() - 2; ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({graphics_controller->count_cell_x()/2 + 3, j})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }
    for(size_t i{graphics_controller->count_cell_x()/2 + 4}; i < graphics_controller->count_cell_x() - 2; ++i)
    {
      ControlContents controlcontents{map->cell_by_indexes({i, graphics_controller->count_cell_y() - 2})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }
    for(size_t i{graphics_controller->count_cell_x()/2 + 3}; i < graphics_controller->count_cell_x() - 2; ++i)
    {
      ControlContents controlcontents{map->cell_by_indexes({i, 1})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }
    for(size_t j{2}; j < graphics_controller->count_cell_y() - 1; ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({graphics_controller->count_cell_x() - 2, j})};
      controlcontents.set_main_landscape(MainLandscapes(5));
    }
    for(size_t j{0}; j < graphics_controller->count_cell_x(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({j, 0})};
      controlcontents.set_main_landscape(MainLandscapes(4));
    }
    for(size_t j{0}; j < graphics_controller->count_cell_x(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({j, graphics_controller->count_cell_y() - 1})};
      controlcontents.set_main_landscape(MainLandscapes(4));
    }

    for(size_t i{0}; i < graphics_controller->count_cell_x(); ++i)
      for(size_t j{0}; j < 2; ++j)
      {
        ControlContents controlcontents{map->cell_by_indexes({i, j})};
        if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
      }
    for(size_t i{0}; i < 2; ++i)
      for(size_t j{0}; j < graphics_controller->count_cell_y(); ++j)
      {
        ControlContents controlcontents{map->cell_by_indexes({i, j})};
        if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
      }
    for(size_t i{graphics_controller->count_cell_x() - 2}; i < graphics_controller->count_cell_x(); ++i)
      for(size_t j{0}; j < graphics_controller->count_cell_y(); ++j)
      {
        ControlContents controlcontents{map->cell_by_indexes({i, j})};
        if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
      }
    for(size_t i{0}; i < graphics_controller->count_cell_x(); ++i)
      for(size_t j{graphics_controller->count_cell_y() - 2}; j < graphics_controller->count_cell_y(); ++j)
      {
        ControlContents controlcontents{map->cell_by_indexes({i, j})};
        if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(7));
      }

    for(size_t i{0}; i < graphics_controller->count_cell_x(); ++i)
      for(size_t j{2}; j < 4; ++j)
      {

        ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
        if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(6));
      }
    size_t map_size_y = graphics_controller->count_cell_y();
    for(size_t i{0}; i < graphics_controller->count_cell_x(); ++i)
      for(size_t j{map_size_y - 4}; j < graphics_controller->count_cell_y(); ++j)
      {

        ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
        if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(6));
      }
    for(size_t i{2}; i < 3; ++i)
      for(size_t j{0}; j < graphics_controller->count_cell_y(); ++j)
      {

        ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
        if(!controlcontents.has_main_landscape())
          controlcontents.set_main_landscape(MainLandscapes(6));
      }
    for(size_t i{0}; i < graphics_controller->count_cell_y(); ++i)
    {

      ControlContents controlcontents{map->cell_by_indexes({graphics_controller->count_cell_x() / 2 - 1, size_t(i)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
    for(size_t i{0}; i < graphics_controller->count_cell_y(); ++i)
    {

      ControlContents controlcontents{map->cell_by_indexes({graphics_controller->count_cell_x() - 3, size_t(i)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
    for(size_t i{0}; i < graphics_controller->count_cell_y(); ++i)
    {
      ControlContents controlcontents{map->cell_by_indexes({graphics_controller->count_cell_x() / 2 + 4, size_t(i)})};
      if(!controlcontents.has_main_landscape())
        controlcontents.set_main_landscape(MainLandscapes(6));
    }
    srand(rand() % 8);
    for(size_t i{0}; i < graphics_controller->count_cell_x(); ++i)
      for(size_t j{0}; j < graphics_controller->count_cell_y(); ++j)
      {
        int type_landscape = 0;
        ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
        if(!controlcontents.has_main_landscape())
        {
          type_landscape = rand() % 7;
          switch (type_landscape)
          {
          case 0:
            controlcontents.set_main_landscape(MainLandscapes(1));
            break;
          case 1:
            controlcontents.set_main_landscape(MainLandscapes(2));
            break;
          default:
            controlcontents.set_main_landscape(MainLandscapes(0));
            break;
          }

          // controlcontents.set_main_landscape(MainLandscapes(rand() % 5));
        }
      }
}

void CreateMap::set_otherlandscapes(Map *map)
{
   for(size_t i{0}; i < graphics_controller->count_cell_x(); ++i)
     for(size_t j{0}; j < graphics_controller->count_cell_y(); ++j)
     {
          ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
          MainLandscapes scape = controlcontents.get_main_landscape();
          if(scape == MainLandscapes(0))
          {
              int other_land = rand() % 4;
              switch (other_land)
              {
                case 0:
                  controlcontents.set_other_landscape(OtherLandscapes(0));
                  break;
                case 1:
                  controlcontents.set_other_landscape(OtherLandscapes(1));
                  break;
                case 2:
                  controlcontents.set_other_landscape(OtherLandscapes(3));
                  break;
                case 3:
                  controlcontents.set_other_landscape(OtherLandscapes(4));


              }

          }
          if(scape == MainLandscapes(6))
          {
               int other_land = rand() % 4;
               switch (other_land)
               {
                 case 0:
                   controlcontents.set_other_landscape(OtherLandscapes(0));
                   break;
                 case 1:
                   controlcontents.set_other_landscape(OtherLandscapes(2));
                   break;
                 case 2:
                   controlcontents.set_other_landscape(OtherLandscapes(3));
                   break;
                 case 3:
                   controlcontents.set_other_landscape(OtherLandscapes(5));


               }

          }
          if(scape == MainLandscapes(2))
          {
              int other_land = rand() % 2;
              switch (other_land)
              {
                case 0:
                  controlcontents.set_other_landscape(OtherLandscapes(0));
                  break;
                case 1:
                  controlcontents.set_other_landscape(OtherLandscapes(1));
                  break;

              }

          }
     }

}



Resources CreateMap::give_resourse(int number)
{
  Resources result = Resources(0);
  if(number <= 9)
    result = Resources(8);
  else if(number >= 10 and number <= 12)
  {
    int some_res = rand() % 2;
    switch (some_res)
    {
    case 0:
      result = Resources(6);
      break;
    case 1:
      result = Resources(4);
      break;
    }
  }
  else if(number >= 13 and number <= 16)
  {
    int some_res = rand() % 3;
    switch (some_res)
    {
    case 0:
      result = Resources(1);
      break;
    case 1:
      result = Resources(2);
      break;
    case 2:
      result = Resources(3);
      break;
    }

  }
  else if(number >= 17 && number <= 19)
  {
    int some_res = rand() % 3;
    switch (some_res)
    {
    case 0:
      result = Resources(5);
      break;
    case 1:
      result = Resources(7);
      break;
    case 2:
      result = Resources(9);
      break;
    }

  }
  else
    throw std::runtime_error("give_resourse(): number must be less 20");

  return result;
}

void CreateMap::add_resource(Map* map)
{
  for(size_t i{0}; i < graphics_controller->count_cell_x(); ++i)
    for(size_t j{0}; j < graphics_controller->count_cell_y(); ++j)
    {
      ControlContents controlcontents{map->cell_by_indexes({size_t(i), size_t(j)})};
      int give_res = rand() % 2;
      if(give_res == 0)
      {
        MainLandscapes scape = controlcontents.get_main_landscape();
        if(scape != MainLandscapes(1) and scape != MainLandscapes(4))
        {
          switch(scape)
          {
          case MainLandscapes(7):
            controlcontents.add_resource(Resources(rand() % 2), rand() % 10);
            break;
          case MainLandscapes(5):
            controlcontents.add_resource(Resources(1), rand() % 10);
            break;
          default:
            Resources res = give_resourse(rand() % 20);
            controlcontents.add_resource(res, rand() % 10);
            break;

          }
        }

        // controlcontents.add_resource(Resources(rand() % 10), rand() % 10);

      }
    }
}

std::vector<Position> CreateMap::initial_pos_player(int num_player, Map* map)
{
  std :: vector<Position> start_positions;
  int x_position, y_position = 0;
  for(int i = 0; i < num_player; ++i)
  {
    Position pos;
    while(true)
    {

      srand(time(0));
      pos.x = rand() % graphics_controller->count_cell_x();
      pos.y = rand() % graphics_controller->count_cell_y();
      ControlContents controlcontents{map->cell_by_indexes({size_t(pos.x), size_t(pos.y)})};
      MainLandscapes scape = controlcontents.get_main_landscape();
      if(scape != MainLandscapes(1) and scape != MainLandscapes(4) and scape != MainLandscapes(7)
              and scape != MainLandscapes(5))
      {
          int control = 0;
          if(start_positions.size() == 0)
          {
              start_positions.push_back(pos);
              break;
          }
          for(int j = 0; j < start_positions.size(); ++j)
              if(pos.x == start_positions[j].x and pos.y == start_positions[j].y)
                  control = 1;
           if(control == 0)
           {
               start_positions.push_back(pos);
               break;
           }
     }
   }
  }

  return start_positions;
}
