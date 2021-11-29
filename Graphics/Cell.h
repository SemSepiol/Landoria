#ifndef CELL_H
#define CELL_H

#include <memory>
#include <vector>

#include <QPainter>
#include <QWidget>

#include "Buildings/Building.h"
#include "Factories/FactoryBuild.h"
#include "Factories/FactoryColor.h"
#include "Factories/FactoryPixmap.h"
#include "Factories/FactoryRes.h"
#include "Factories/FactoryUnits.h"
#include "GraphicsController/Calculations.h"
#include "ICell.h"
#include "IContent.h"
#include "IMap.h"
#include "Resources/Res.h"
#include "Units/Unit.h"
#include "../Controllers/Enums.h"


struct Content
{
  std::unique_ptr<IContent> content;
  bool show_content = true;
  bool highlight = false;
  Content(IContent* _content) : content{_content} {}
};


class Cell : public ICell
{
public:
  Cell(IMap* map);

  // point - центр клетки
  virtual void draw(QPoint point) override;
  void draw_borders(QPoint point);
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;

  // точка относительно центра клетки
  IContent* click(QPoint pos);

private:
  void draw_cell(QPoint point);
  void draw_landscape(QPoint point);
  void draw_contents(QPoint point);
  void draw_fog_of_war(QPoint point);
  void draw_highlight(QPoint point);
  Countries cell_country(Position pos_cell);

  void draw_unit(Content* content, QPoint point_cell, int count_drawn_unit);
  void draw_resource(Content* content, QPoint point_cell);
  void draw_building(Content* content, QPoint point_cell);

  IMap* map;
  std::vector<Content> contents;

  bool is_there_main_landscape = false;
  bool is_there_other_landscape = false;
  MainLandscapes mainlandscape = MainLandscapes::Plain;
  OtherLandscapes otherlandscape= OtherLandscapes::Nothing;
  Countries country = Countries::Nothing;

  ShowCell show_cell = Show;

  friend class ControlContents;
};


class ControlContents : public IObject
{
public:
  ControlContents(Cell* _cell) : cell{_cell}{}
  ControlContents(ICell* _cell) : cell{static_cast<Cell*>(_cell)}{}

  void set_main_landscape(MainLandscapes type_landscape);
  void set_other_landscape(OtherLandscapes type_landscape);
  IContent* add_resource(Resources type_resource, int count_of_res = 0);
  IContent* add_building(Buildings type_building);
  IContent* add_unit(Units type_unit);
  void add_unit(IContent* unit);

  void del_content(IContent* content);
  void del_building();
  IContent* pop_content(IContent* content);

  MainLandscapes get_main_landscape() const;
  OtherLandscapes get_other_landscape() const;
  Resources get_resource() const;
  Building* get_building() const;
  std::vector<Units> get_units() const;
  Countries get_country_units() const;

  bool has_main_landscape() const;
  bool has_other_landscape() const;
  bool has_resource() const;
  bool has_building() const;
  int count_units() const;

  void set_show_cell(ICell::ShowCell show_cell);
  ICell::ShowCell get_show_cell() const;
  void set_show_res(bool show_res);
  void set_show_unit(bool show_unit, class Unit* unit);
  void set_highlight_unit(IContent* unit, bool highlight);

  void set_count_of_res(int count);
  int get_count_of_res() const;

  void set_country(Countries country);
  Countries get_country() const;

  virtual ~ControlContents() {}
private:
  Res* _get_resource() const;
  class Building* _get_building() const;
  std::vector<class Unit*> _get_units() const;

  Cell* cell;
};

#endif // CELL_H
