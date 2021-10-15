#ifndef MENUTOWN_H
#define MENUTOWN_H

#include <memory>

#include "IMenuTown.h"
#include "../../Controllers/Player/IPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../../Controllers/Player/PlayerTown.h"
#include "MenuBuildTown.h"

class MenuTown : public IMenuTown
{
public:
  MenuTown(ITownMenuGraphicsController* graphics_controller, PlayerTown* town);
  void set_geometry(QPoint pos, Size size);
  void start();

private:
  std::unique_ptr<MenuBuildTown> menu_build_town;
};

#endif // MENUTOWN_H
