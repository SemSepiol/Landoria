#ifndef MAP_H
#define MAP_H

#include <memory>
#include <vector>

#include "Cell.h"
#include "IMap.h"
#include "../GameWindow.h"
#include "../GraphicsController/Calculations.h"
#include "../GraphicsController/IMapGraphicsController.h"



class Map : public IMap, public IMapForFind
{

public:
  Map(IMapGraphicsController* graphics_controller);

  // point - центр карты
  void do_cells();

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  virtual ~Map() override {}

  virtual ICell* icell_by_indexes(Position pos) const override;
  Cell* cell_by_indexes(Position pos) const;
  Position indexes_by_cell(Cell* cell) const;
  Position indexes_by_cell(ICell* cell) const override;
  virtual std::vector<Position> adjacent_cells(Position pos) const override;
  virtual void set_cell_country(Position pos_cell, Countries coutry) override;
  virtual Countries get_cell_country(Position pos_cell) override;
  std::pair<Cell*, IContent*> click(QPoint pos);
  QPoint point_of_cell_in_win(Position pos);

  void set_type_map(TypeMap type_map);
  virtual const TypeMap& get_type_map() const override;

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

  TypeMap type_map;
};

#endif // MAP_H
