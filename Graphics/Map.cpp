#include "Map.h"

Map::Map(IGame* game)
  :IMap{}, game_controller{game}
{

}

void Map::draw(QPoint point)
{

}

QWidget* Map::window(){
  return game_controller->window();
}

