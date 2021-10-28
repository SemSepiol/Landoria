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
             PlayerUnit* unit, Cell* cell);

protected:
  void set_buttons() override;
  virtual void draw_butt(size_t num_butt) override;
  virtual void click_butt(size_t num_butt) override;
  void set_is_enable(MyButton& my_butt);

  bool has_menu = false;
  std::unique_ptr<MenuBuild> menu;
  size_t num_butt_build;
};

class MenuBuild : public AMenuForUnit
{
public:
  MenuBuild(QWidget* win, IUnitMenuGraphicsController* graphics_controller,
            PlayerUnit* unit, Cell* cell);
  virtual void set_geometry(QPoint pos, int side_square) override;
protected:
  void set_buttons() override;
  QRectF rect_butt(size_t i) override;
  void set_is_enable();
};

#endif // WORKERMENU_H
