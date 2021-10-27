#ifndef UNIT_H
#define UNIT_H

#include <QPainter>

#include "../IContent.h"
#include "../../Controllers/Enums.h"
#include "../Factories/FactoryPixmap.h"
#include "../Factories/FactoryColor.h"
#include "../ICell.h"

class Unit : public IContent
{
public:
  Unit(ICell* _cell)
    : cell{_cell}
  {}

  virtual void draw(QPoint point) override;
  virtual QWidget* window() const override;
  virtual Calculations* calculations() const override;
  virtual Contents what_content_I() const override {return Contents::Unit;}
  virtual Units what_unit_I() const = 0;

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
};

#endif // UNIT_H
