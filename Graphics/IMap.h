#ifndef IMAP_H
#define IMAP_H

#include <QPoint>
#include <QWidget>

#include "GraphicsController/Calculations.h"
#include "ICell.h"
#include "IDrawObject.h"
#include "../Controllers/Enums.h"


struct TypeMap
{
  enum Overlay {
    NoOverlay,
    Political,
    HighlightResources
  };

  enum TypeContent{
    All,
    Nothing,
    Units,
    Resources,
    Building,
  };

  Overlay overplay = NoOverlay;
  TypeContent type_content = All;
  bool show_notvisible = true;
  bool show_other_landscapes = true;
};


class IMapForFind : public IObject
{
public:
  virtual ICell* icell_by_indexes(Position pos) const = 0;
  virtual std::vector<Position> adjacent_cells(Position pos) const = 0;
  virtual void set_cell_country(Position pos_cell, Countries coutry) = 0;
  virtual Countries get_cell_country(Position pos_cell) = 0;
};


class IMap : public IDrawObject
{
public:
  // point - центр карты
  virtual void draw(QPoint point) override = 0;
  virtual QWidget* window() const override = 0;
  virtual Calculations* calculations() const override = 0;
  virtual std::vector<Position> adjacent_cells(Position pos) const = 0;

  virtual Position indexes_by_cell(ICell* cell) const = 0;
  virtual ICell* icell_by_indexes(Position pos) const = 0;

  virtual const TypeMap& get_type_map() const = 0;
};

#endif // IMAP_H
