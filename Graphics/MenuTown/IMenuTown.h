#ifndef IMENUTOWN_H
#define IMENUTOWN_H

#include <QWidget>

#include "../../IObject.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"

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

  virtual void set_type_work(TypeWork _type_work) = 0;
};

#endif // IMENUTOWN_H
