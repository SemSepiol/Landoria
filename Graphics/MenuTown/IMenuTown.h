#ifndef IMENUTOWN_H
#define IMENUTOWN_H

#include <QWidget>

#include "../../IObject.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsControllerFor.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "AWidgetTown.h"

class IMenuTown : public IObject
{
public:
  enum TypeWork
  {
    EditProject,
    AddQueue
  };

  virtual ITownMenuGraphicsController* graphics_controller() const = 0;
  virtual QWidget* window() const = 0;
  virtual PlayerTown* town() const = 0;
  virtual IMenuTownPlayer* player() const = 0;

  virtual void delete_townmenu() = 0;
  virtual void open_menu_build() = 0;
  virtual void open_menu_alreadybuild() = 0;

  virtual void set_build(Units type_unit) = 0;
  virtual void set_build(TownBuildings type_building) = 0;
  virtual void del_build_from_queue(AWidgetTown* wid) = 0;
  virtual size_t num_from_queue(AWidgetTown* wid) const = 0;
  virtual size_t count_from_queue() const = 0;
  virtual void move_up_build(AWidgetTown* wid) = 0;
  virtual void move_down_build(AWidgetTown* wid) = 0;
  virtual void wheel_scroll(int angle_delta) = 0;

  virtual void do_inform_widget(QString text) = 0;
  virtual void del_inform_widget() = 0;

  virtual void set_type_work(TypeWork _type_work) = 0;
  virtual TypeWork get_type_work() const = 0;
};

#endif // IMENUTOWN_H
