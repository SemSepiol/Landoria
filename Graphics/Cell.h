#ifndef CELL_H
#define CELL_H
#include <memory>
#include <vector>
#include <QPainter>
#include <QWidget>

#include "IMap.h"
#include "ICell.h"
#include "IContent.h"

#include "../Controller/Enums.h"
#include "../Controller/Calculations.h"

#include "Factories/FactoryBuild.h"
#include "Factories/FactoryUnits.h"
#include "Factories/FactoryRes.h"
#include "Factories/FactoryPixmap.h"

#include "Resources/Res.h"
#include "Units/Unit.h"
#include "Buildings/Building.h"

class Cell : public ICell
{
public:
  Cell(IMap* map);

  // point - центр клетки
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  // точка относительно центра клетки
  IContent* click(QPoint pos);


private:
  IMap* map;
  std::vector<std::unique_ptr<IContent>> contents;

  bool is_there_main_landscape = false;
  bool is_there_other_landscape = false;
  MainLandscapes mainlandscape = MainLandscapes::Plain;
  OtherLandscapes otherlandscape= OtherLandscapes::Nothing;

  friend class ControlContents;
};


class ControlContents : public IObject
{
public:
  ControlContents(Cell* cell) : cell{cell}{}

  void set_main_landscape(MainLandscapes type_landscape);
  void set_other_landscape(OtherLandscapes type_landscape);
  void add_resource(Resources type_resource);
  void add_building(Buildings type_building);
  void add_unit(Units type_unit);

  void del_content(IContent* content);

  MainLandscapes get_landscape() const;
  Resources get_resource() const;
  Buildings get_building() const;
  std::vector<Units> get_units() const;

  bool has_landscape() const;
  bool has_resource() const;
  bool has_building() const;
  int count_units();

  virtual ~ControlContents() {}
private:
  Cell* cell;
};

#endif // CELL_H
