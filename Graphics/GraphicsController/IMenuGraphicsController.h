#ifndef IMENUGRAPHICSCONTROLLER_H
#define IMENUGRAPHICSCONTROLLER_H

#include <QPoint>
#include <QWidget>

#include "../Units/Unit.h"
#include "../../Controllers/Player/PlayerScience.h"
#include "../../IObject.h"


class IMenuInWindowGraphicsController : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual void move_map(QPoint move_point) = 0;
  virtual void exit() = 0;
  virtual void show_minimap() = 0;
  virtual void next_move() = 0;

  virtual void do_inform_widget(std::vector<std::pair<QString, QColor>> text) = 0;
  virtual void del_inform_widget() = 0;

  virtual void open_menu_lists() = 0;
  virtual void close_menu_lists() = 0;

  virtual void open_menu_science() = 0;
  virtual void close_menu_science() = 0;
};


class IUnitMenuGraphicsController : public IObject
{
public:
  virtual void menu_unit_event(class Unit* unit, Event* event) = 0;
  virtual PlayerScience* player_science() = 0;
};


class ITownMenuGraphicsController : public IObject
{
public:
  virtual QWidget* window() const = 0;
  virtual void delete_townmenu() = 0;
  virtual void do_inform_widget(std::vector<std::pair<QString, QColor>> text) = 0;
  virtual void del_inform_widget() = 0;
};

class IMenuGraphicsControllerFull : public IMenuInWindowGraphicsController,
    public IUnitMenuGraphicsController, public ITownMenuGraphicsController
{
public:
  virtual void del_menu_unit() = 0;
  virtual void press_escape() = 0;
};

#endif // IMENUGRAPHICSCONTROLLER_H
