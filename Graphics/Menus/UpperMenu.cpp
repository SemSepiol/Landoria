#include "UpperMenu.h"
#include <iostream>

UpperMenu::UpperMenu(IGraphicsControllerForMenuInWindow* _graphic_controller)
  : AMenuInWindow(_graphic_controller)
{}

void UpperMenu::mouseMoveEvent(QMouseEvent *event)
{
  if(event->pos().y() < 5)
    graphics_controller->move_map({0, 50});
}

void UpperMenu::draw()
{
  QPainter qp(this);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_exit();
  QRectF source = FactoryPixmap().size_picture_content();
  qp.drawPixmap(exit_butt(), pixmap, source);

  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QPoint p1 = QPoint{0, height_menu};
  QPoint p2 = QPoint{width_menu, height_menu};
  qp.drawLine(p1, p2);
}

QRect UpperMenu::exit_butt() const
{
  QPoint topleft = QPoint{width_menu - height_menu, 0};
  QPoint bottomright = QPoint{width_menu, height_menu};
  return QRect{topleft, bottomright};
}

void UpperMenu::click(QPoint pos)
{
  if (point_in_rect(exit_butt(), pos))
    graphics_controller->exit();
}
