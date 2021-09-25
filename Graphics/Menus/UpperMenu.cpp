#include "UpperMenu.h"
#include <iostream>

UpperMenu::UpperMenu(IGraphicsForUpperMenu* graphic_controller)
  : QWidget{graphic_controller->window()} ,graphic_controller{graphic_controller}
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
  draw();
}

void UpperMenu::mouseReleaseEvent(QMouseEvent* event)
{
  if (point_in_rect(exit_butt(), event->pos()))
    graphic_controller->exit();
}

void UpperMenu::click_exit()
{
  graphic_controller->exit();
}

void UpperMenu::draw()
{
  QPainter qp(this);

  QPixmap pixmap{":/Graphics/image/menu/exit.png"};
  QRectF source{0., 0., 100., 100.};
  qp.drawPixmap(exit_butt(), pixmap, source);

}

QRect UpperMenu::exit_butt() const
{
  QPoint topleft = {width_menu - height_menu, 0};
  QPoint bottomright = {width_menu, height_menu};
  return QRect{topleft, bottomright};
}

bool UpperMenu::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
