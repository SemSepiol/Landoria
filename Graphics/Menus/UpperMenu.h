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
  UpperMenu(IGraphicsControllerForMenuInWindow* graphic_controller);

protected:
  virtual void draw() override;
  virtual void click(QPoint pos) override;
  QRect exit_butt() const;
};

#endif // UPPERMENU_H
