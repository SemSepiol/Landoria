#ifndef BOTTOMMENU_H
#define BOTTOMMENU_H

#include "../GraphicsController/IGraphicsController.h"
#include "AMenuInWindow.h"

class BottomMenu : public AMenuInWindow
{
public:
  BottomMenu(IMenuInWindowGraphicsController* graphic_controller);
  virtual void mouseMoveEvent(QMouseEvent *event) override;
protected:
  virtual void draw() override;
  virtual void click(QPoint pos) override;

  virtual QRect show_minimap_butt() const;
  virtual QRect next_move_butt() const;
};

#endif // BOTTOMMENU_H
