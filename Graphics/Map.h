#ifndef MAP_H
#define MAP_H
#include <memory>
#include <vector>

#include "GameWindow.h"
#include "IMap.h"
#include "Cell.h"
#include "GraphicsController/IGraphicsController.h"
#include "GraphicsController/Calculations.h"


class Map : public IMap
{

public:
  Map(IMapGraphicsController* graphics_controller);

  // point - центр карты
  void do_cells();

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual ~Map() override {}

  Cell* cell_by_indexes(Position pos) const;
  Position indexes_by_cell(Cell* cell) const;
  std::vector<Position> adjacent_cells(Position pos) const;
  std::pair<Cell*, IContent*> click(QPoint pos);
  QPoint point_of_cell_in_win(Position pos);

private:
  int sign(int a);
  int coord_to_cub_index(int a);

  // точка центра клетки относительно левого верхнего угла
  QPoint point_of_cell(Position pos);

  // выдает индекс в массиве клетки,
  // если точка не в клетки, то выдает {count_cell_y(), count_cell_x()}
  Position point_to_indexes_cell(QPoint pos);

  IMapGraphicsController* graphics_controller;
  std::vector<std::vector<std::unique_ptr<Cell>>> cells;
};

#endif // MAP_H
