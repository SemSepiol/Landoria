#ifndef MENUTOWN_H
#define MENUTOWN_H

#include <memory>

#include "IMenuTown.h"
#include "../../Controllers/Player/IMenuTownPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "MenuBuildTown.h"
#include "MenuTypeWorkTown.h"

class MenuTown : public IMenuTown
{
public:
  MenuTown(IMenuTownPlayer* player, ITownMenuGraphicsController* graphics_controller, PlayerTown* town);
  void set_geometry(QPoint pos, Size size);
  void start();

  virtual ITownMenuGraphicsController* graphics_controller() const override;
  virtual QWidget* window() const override;
  virtual PlayerTown* town() const override;
  virtual void delete_townmenu() override;
  virtual void open_menu_build() override;
  virtual void open_menu_alreadybuild() override;
private:
  void close_menu_build();
  void close_menu_alreadybuild();

  void set_geometry_menu_build();
  void set_geometry_menu_selectwork();

  IMenuTownPlayer* _player;
  ITownMenuGraphicsController* _graphics_controller;
  PlayerTown* _town;

  std::unique_ptr<MenuBuildTown> menu_build_town;
  std::unique_ptr<MenuTypeWorkTown> menu_type_work_town;

  QPoint pos;
  Size size;
};

#endif // MENUTOWN_H
