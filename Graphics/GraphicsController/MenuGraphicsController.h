#ifndef MENUGRAPHICSCONTROLLER_H
#define MENUGRAPHICSCONTROLLER_H

#include "IMenuGraphicsController.h"
#include "IGraphicsController.h"


class MenuGraphicsController : public IMenuGraphicsControllerFull
{
public:
  MenuGraphicsController(IGraphicsController* graphics_controller);

  virtual QWidget* window() const override;
  virtual void move_map(QPoint move_point) override;
  virtual void exit() override;
  virtual void show_minimap() override;
  virtual void next_move() override;

  virtual void menu_unit_event(class Unit* unit, Event* event) override;

  virtual void delete_townmenu() override;
  virtual void do_inform_widget(std::vector<std::pair<QString, QColor>> text) override;
  virtual void del_inform_widget() override;

  void create_uppermenu();
  void create_bottommenu();
  virtual void del_menu_unit() override;
private:
  IGraphicsController* graphics_controller;
};

#endif // MENUGRAPHICSCONTROLLER_H
