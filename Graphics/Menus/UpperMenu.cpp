#include "UpperMenu.h"
#include <iostream>

UpperMenu::UpperMenu(IGraphicsForUpperMenu* graphic_controller)
  : IMenu{graphic_controller->window()} ,graphic_controller{graphic_controller}
{
  QObject::setParent(graphic_controller->window());
}

UpperMenu::~UpperMenu()
{
//  exit.~unique_ptr();
}

void UpperMenu::set_size()
{
  width_menu = graphic_controller->width_menu();
  height_menu = graphic_controller->height_menu();
//  std::cout << width_menu << " " << height_menu << std::endl;
  QWidget::resize(width_menu, height_menu);
}

void UpperMenu::paintEvent(QPaintEvent* event)
{
  draw(graphic_controller->uppermenu_top_left());
}

void UpperMenu::mouseReleaseEvent(QMouseEvent* event)
{
  if (point_in_rect(exit_butt(pos), event->pos()))
    graphic_controller->exit();
}

void UpperMenu::draw(QPoint point)
{
  pos = point;
  QPainter qp(this);

  QPixmap pixmap{":/Graphics/image/menu/exit.png"};
  QRectF source{0., 0., 100., 100.};
  qp.drawPixmap(exit_butt(point), pixmap, source);

  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QPoint p1 = pos + QPoint{0, height_menu};
  QPoint p2 = pos + QPoint{width_menu, height_menu};
  qp.drawLine(p1, p2);

}

QRect UpperMenu::exit_butt(QPoint point) const
{
  QPoint topleft = point + QPoint{width_menu - height_menu, 0};
  QPoint bottomright = point + QPoint{width_menu, height_menu};
  return QRect{topleft, bottomright};
}

bool UpperMenu::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
