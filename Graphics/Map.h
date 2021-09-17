#ifndef MAP_H
#define MAP_H
#include <memory>
#include <vector>

#include "GameWindow.h"
#include "IMap.h"
#include "Cell.h"
#include "../Controller/IGame.h"
#include "../Controller/Calculations.h"

struct CubicCoordinates
{
  CubicCoordinates(int a, int b);
  CubicCoordinates(int x, int y, int z);
  int x;
  int y;
  int z;
};

class Map : public IMap
{

public:
  Map(IGameForMap* game);

  // point - центр карты
  void do_cells();

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual ~Map() override {}

  Cell* cell_by_index(size_t x, size_t y);
  IContent* click(QPoint pos);

private:
  int sign(int a);
  int coord_to_cub_index(int a);
  IGameForMap* game_controller;
  std::vector<std::vector<std::unique_ptr<Cell>>> cells;
};

#endif // MAP_H
