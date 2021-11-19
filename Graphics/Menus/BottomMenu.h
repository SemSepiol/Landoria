#ifndef BOTTOMMENU_H
#define BOTTOMMENU_H

#include <sstream>

#include "../GraphicsController/IMenuGraphicsController.h"
#include "AMenuInWindow.h"
#include "../Cell.h"
#include "../Factories/FactoryString.h"

class BottomMenu : public AMenuInWindow
{
public:
  BottomMenu(IMenuInWindowGraphicsController* graphic_controller);

  void update_infofm(Cell* cell);
  void del_inform();

protected:
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void draw() override;
  virtual void click(QPoint pos) override;

  void draw_text();

  virtual QRect show_minimap_butt() const;
  virtual QRect next_move_butt() const;

  Cell* cell = nullptr;
};

#endif // BOTTOMMENU_H
