#ifndef BOTTOMMENU_H
#define BOTTOMMENU_H

#include <sstream>

#include "AMenuInWindow.h"
#include "../../Factories/FactoryString.h"
#include "../../GraphicsController/IMenuGraphicsController.h"
#include "../../Map/Cell.h"


class BottomMenu : public AMenuInWindow
{
public:
  BottomMenu(IMenuInWindowGraphicsController* graphic_controller);

  void update_infofm(Cell* cell);
  void del_inform();

  QRect open_type_map_butt() const;
protected:
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void draw() override;
  virtual void click(QPoint pos) override;

  void draw_text();

  QRect show_minimap_butt() const;
  QRect next_move_butt() const;

  Cell* cell = nullptr;
};

#endif // BOTTOMMENU_H
