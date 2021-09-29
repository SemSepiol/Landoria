#ifndef CELL_H
#define CELL_H
#include <memory>
#include <vector>
#include <QPainter>
#include <QWidget>

#include "IMap.h"
#include "ICell.h"
#include "IContent.h"

#include "../Controllers/Enums.h"
#include "GraphicsController/Calculations.h"

#include "Factories/FactoryBuild.h"
#include "Factories/FactoryUnits.h"
#include "Factories/FactoryRes.h"
#include "Factories/FactoryPixmap.h"

#include "Resources/Res.h"
#include "Units/Unit.h"
#include "Buildings/Building.h"

struct Content
{
  std::unique_ptr<IContent> content;
  bool show_content = true;
  Content(IContent* _content) : content{_content} {}
};

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
  std::vector<Content> contents;

  bool is_there_main_landscape = false;
  bool is_there_other_landscape = false;
  MainLandscapes mainlandscape = MainLandscapes::Plain;
  OtherLandscapes otherlandscape= OtherLandscapes::Nothing;

  bool show_cell = true;

  friend class ControlContents;
};


class ControlContents : public IObject
{
public:
  ControlContents(Cell* cell) : cell{cell}{}

  void set_main_landscape(MainLandscapes type_landscape);
  void set_other_landscape(OtherLandscapes type_landscape);
  IContent* add_resource(Resources type_resource);
  IContent* add_building(Buildings type_building);
  IContent* add_unit(Units type_unit);
  void add_unit(IContent* unit);

  void del_content(IContent* content);
  IContent* pop_content(IContent* content);

  MainLandscapes get_landscape() const;
  Resources get_resource() const;
  Buildings get_building() const;
  std::vector<Units> get_units() const;

  bool has_landscape() const;
  bool has_resource() const;
  bool has_building() const;
  int count_units() const;

  void set_show_cell(bool show_cell);
  void set_show_res(bool show_res);
  void set_show_unit(bool show_unit, class Unit* unit);

  virtual ~ControlContents() {}
private:
  Cell* cell;
};

#endif // CELL_H
