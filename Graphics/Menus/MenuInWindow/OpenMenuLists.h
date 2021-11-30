#ifndef OPENMENULISTS_H
#define OPENMENULISTS_H

#include <QWidget>

#include "AMenuInWindow.h"
#include "../../GraphicsController/IMenuGraphicsController.h"

class OpenMenuLists : public AMenuInWindow
{
public:
  OpenMenuLists(IMenuInWindowGraphicsController* graphics_controller);
  virtual void draw() override;
  virtual void click(QPoint pos) override;
  void switch_arrow();

private:
  bool is_menu_open = false;

};

#endif // OPENMENULISTS_H
