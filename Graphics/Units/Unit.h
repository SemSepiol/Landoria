#ifndef UNIT_H
#define UNIT_H

#include <QPainter>

#include "UnitsCharaterichtics.h"
#include "../IContent.h"
#include "../Factories/FactoryColor.h"
#include "../Factories/FactoryPixmap.h"
#include "../Map/ICell.h"
#include "../../Controllers/Enums.h"


class Unit : public IContent
{
public:
  enum TypeUnit
  {
    Peaceful,
    RangedCombat,
    CloseCombat,
    Cavalry
  };

  Unit(ICell* _cell);

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override {return Contents::Unit;}
  virtual Units what_unit_I() const = 0;
  virtual TypeUnit what_my_type() const = 0;

  virtual void set_standard_charaterichtics();
  void set_health(int health);
  int get_health() const;
  void set_max_health(int max_health);
  int get_max_health() const;
  void set_movement(int movement);
  int get_movement() const;
  void set_max_movement(int max_movement);
  int get_max_movement() const;
  void set_vision(int vision);
  int get_vision() const;

  void set_country(Countries country);
  Countries get_country() const;
private:
  ICell* cell;
  int max_health;
  int health;
  int max_movement;
  int movement;
  int vision;
  Countries country;

  std::unique_ptr<QPixmap> pixmap_for_unit;
};

#endif // UNIT_H
