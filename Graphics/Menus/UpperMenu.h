#ifndef UPPERMENU_H
#define UPPERMENU_H

#include <QPainter>
#include <QMouseEvent>

#include "AMenuInWindow.h"
#include "../Factories/FactoryPixmap.h"
#include "../GraphicsController/IGraphicsController.h"

class UpperMenu : public AMenuInWindow
{
public:
  UpperMenu(IMenuInWindowGraphicsController* graphic_controller);

  void set_enable_move_map(bool enable_move_map);
protected:
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void draw() override;
  virtual void click(QPoint pos) override;
  QRect exit_butt() const;

  bool enable_move_map = true;
};

#endif // UPPERMENU_H
