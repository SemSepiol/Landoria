#ifndef MENUSTARTGRAPHICSCONTROLLER_H
#define MENUSTARTGRAPHICSCONTROLLER_H

#include "IGraphicsController.h"
#include "IMenuStartGraphicsController.h"

#include "../Menus/ManuStart/StartMenu.h"

class MenuStartGraphicsController : public IMenuStartGraphicsController
{
public:
  MenuStartGraphicsController(IGraphicsController* graphics_controller);
  void do_start_menu();

  virtual QWidget* window() const override;
  virtual void start_game() override;

private:
  IGraphicsController* graphics_controller;

  std::unique_ptr<StartMenu> menu_start;
};

#endif // MENUSTARTGRAPHICSCONTROLLER_H
