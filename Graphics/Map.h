#ifndef MAP_H
#define MAP_H
#include <memory>
#include <vector>

#include "GameWindow.h"
#include "IMap.h"
#include "Cell.h"
#include "GraphicsController/IGraphicsController.h"
#include "GraphicsController/Calculations.h"

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
  Map(IGraphicsControllerForMap* game);

  // point - центр карты
  void do_cells();

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual ~Map() override {}

  Cell* cell_by_index(size_t x, size_t y);
  std::pair<Cell*, IContent*> click(QPoint pos);

private:
  int sign(int a);
  int coord_to_cub_index(int a);

  // выдает индекс в массиве клетки,
  // если точка не в клетки, то выдает {count_cell_y(), count_cell_x()}
  std::pair<size_t, size_t> point_to_indexes_cell(QPoint pos);

  // точка центра клетки относительно левого верхнего угла
  QPoint point_of_cell(size_t ind_x, size_t ind_y);

  IGraphicsControllerForMap* graphics_controller;
  std::vector<std::vector<std::unique_ptr<Cell>>> cells;
};

#endif // MAP_H
