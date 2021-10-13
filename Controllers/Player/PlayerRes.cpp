#include "PlayerRes.h"

PlayerRes::PlayerRes()
{
  for(int i{0}; i < CountInEnums().resources(); ++i)
    player_resources.insert({Resources(i), 0});
}

void PlayerRes::add_resource(Resources type_res, int count)
{
  player_resources.at(type_res) += count;
}

void PlayerRes::del_resource(Resources type_res, int count)
{
  player_resources.at(type_res) -= count;
  if(player_resources.at(type_res) < 0)
    player_resources.at(type_res) = 0;
}

void PlayerRes::set_resource(Resources type_res, int count)
{
  player_resources.at(type_res) = count;
}

int PlayerRes::get_resource(Resources type_res)
{
  return player_resources.at(type_res);
}
