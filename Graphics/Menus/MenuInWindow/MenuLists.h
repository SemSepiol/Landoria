#ifndef MENULISTS_H
#define MENULISTS_H

#include "AMenuInWindow.h"

class MenuLists : public AMenuInWindow
{
public:
  MenuLists(IMenuInWindowGraphicsController* graphics_controller);
  virtual void draw() override;
  virtual void click(QPoint pos) override;
};

#endif // MENULISTS_H
