#include "BuildInTown.h"

int BuildInTown::build(int town_production)
{
  if(need_production > town_production)
  {
    need_production -= town_production;
    return 0;
  }
  else{
    int remains = town_production - need_production;
    need_production = 0;
    return remains;
  }
}

void BuildInTown::build_next_level()
{
  need_production = TownBuildNeeds().get_build_need_production(building, level+1);
}
