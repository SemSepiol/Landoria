#ifndef BUILDING_H
#define BUILDING_H

#include <QPainter>

#include "../../Controllers/Enums.h"
#include "../Factories/FactoryPixmap.h"
#include "../ICell.h"
#include "../IContent.h"
#include "BuildingCharaterichtics.h"

class Building : public IContent
{
public:
  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override {return Contents::Building;}
  virtual Buildings what_building_I() const = 0;

  void set_standard_charaterichtics();
  void set_build_phase(int phase);
  void set_end_build_phase(int end_phase);
  int get_build_phase() const;
  int get_end_build_phase() const;

  bool is_built() const;
protected:
  Building(ICell* cell) : cell{cell}{}
private:
  void draw_build_phase(QPoint point);

  ICell* cell;
  int phase = 0;
  int end_phase = 0;
};

#endif // BUILDING_H
