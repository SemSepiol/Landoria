#ifndef MENUTOWN_H
#define MENUTOWN_H

#include <memory>

#include "IMenuTown.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "MenuBuildTown.h"
#include "MenuTypeWorkTown.h"
#include "MenuQueueTown.h"

class MenuTown : public IMenuTown
{
public:  
  MenuTown(IMenuTownPlayer* player, ITownMenuGraphicsController* graphics_controller, PlayerTown* town);
  void set_geometry(QPoint pos, Size size);
  void start();

  virtual ITownMenuGraphicsController* graphics_controller() const override;
  virtual QWidget* window() const override;
  virtual PlayerTown* town() const override;
  virtual IMenuTownPlayer* player() const override;
  virtual void delete_townmenu() override;
  virtual void open_menu_build() override;
  virtual void open_menu_alreadybuild() override;

  virtual void set_build(Units type_unit) override;
  virtual void set_build(TownBuildings type_building) override;

  void set_type_work(TypeWork _type_work) override;
private:
  void close_menu_build();
  void close_menu_alreadybuild();
  void close_menu_queue();

  void set_geometry_menu_build();
  void set_geometry_menu_selectwork();
  void set_geometry_menu_queue();

  IMenuTownPlayer* _player;
  ITownMenuGraphicsController* _graphics_controller;
  PlayerTown* _town;

  std::unique_ptr<MenuBuildTown> menu_build_town;
  std::unique_ptr<MenuTypeWorkTown> menu_type_work_town;
  std::unique_ptr<MenuQueueTown> menu_queue_town;

  QPoint pos;
  Size size;

  TypeWork type_work = TypeWork::AddQueue;
};

#endif // MENUTOWN_H
