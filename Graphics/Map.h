#ifndef MAP_H
#define MAP_H
#include <memory>
#include <vector>

#include "GameWindow.h"
#include "IMap.h"
#include "Cell.h"
#include "../Controller/IGame.h"


class Map : public IMap
{

public:
  Map(IGame* game);

  virtual void draw(QPoint point) override;
  virtual QWidget* window() override;

  virtual ~Map() override {}

private:
  std::unique_ptr<IGame> game_controller;
  std::vector<std::unique_ptr<Cell>> cells;
};

#endif // MAP_H
