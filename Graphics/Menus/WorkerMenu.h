#ifndef WORKERMENU_H
#define WORKERMENU_H

#include <QPoint>
#include <QObject>

#include "AMenuForUnit.h"
#include "../GraphicsController/EventsStructures.h"
#include "../Cell.h"

class MenuBuild;

class WorkerMenu : public AMenuForUnit
{
public:
  WorkerMenu(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
             class Unit* unit, Cell* cell);

protected:
  virtual void draw_butt(size_t num_butt) override;
  virtual void click_butt(size_t num_butt) override;

  bool has_menu = false;
  std::unique_ptr<MenuBuild> menu;
};

class MenuBuild : public AMenuForUnit
{
public:
  MenuBuild(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
            class Unit* unit, Cell* cell);
  virtual void set_geometry(QPoint pos, int side_square) override;
protected:
  QRectF rect_butt(size_t i) override;
  void set_is_enable();
};

#endif // WORKERMENU_H
