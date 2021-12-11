#ifndef IMENUGRAPHICSCONTROLLERFULL_H
#define IMENUGRAPHICSCONTROLLERFULL_H

#include "IMenuGraphicsController.h"
#include "../Menus/MenuInWindow/BottomMenu.h"
#include "../Menus/MenuInWindow/UpperMenu.h"

class IMenuGraphicsControllerFull : public IMenuInWindowGraphicsController,
    public IUnitMenuGraphicsController, public ITownMenuGraphicsController
{
public:
  virtual void del_menu_unit() = 0;
  virtual void press_escape() = 0;
  virtual void event_open_menu_type_map() = 0;
  virtual BottomMenu* get_bottom_menu() = 0;
  virtual UpperMenu* get_upper_menu() = 0;
};

#endif // IMENUGRAPHICSCONTROLLERFULL_H
