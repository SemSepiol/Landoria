#ifndef BOTTOMMENU_H
#define BOTTOMMENU_H

#include "../GraphicsController/IGraphicsController.h"
#include "AMenuInWindow.h"

class BottomMenu : public AMenuInWindow
{
public:
  BottomMenu(IGraphicsControllerForMenuInWindow* graphic_controller);

protected:
  virtual void draw() override;
  virtual void click(QPoint pos) override;

  virtual QRect show_minimap_butt() const;
};

#endif // BOTTOMMENU_H
