#ifndef MAP_H
#define MAP_H
#include <memory>
#include <vector>

#include "GameWindow.h"
#include "IMap.h"
#include "Cell.h"
#include "../Controller/IGame.h"
#include "../Controller/Calculations.h"


class Map : public IMap
{

public:
  Map(IGame* game);

  // point - центр карты
  void do_cells();

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual ~Map() override {}

  Cell* cell_by_index(size_t x, size_t y);

private:
  IGame* game_controller;
  std::vector<std::vector<std::unique_ptr<Cell>>> cells;
};

#endif // MAP_H
