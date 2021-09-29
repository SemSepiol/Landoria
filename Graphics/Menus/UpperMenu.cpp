#include "UpperMenu.h"
#include <iostream>

UpperMenu::UpperMenu(IGraphicsControllerForUpperMenu* graphic_controller)
  : QWidget{graphic_controller->window()} ,graphic_controller{graphic_controller}
{

}

UpperMenu::~UpperMenu()
{
//  exit.~unique_ptr();
}

void UpperMenu::set_geometry(QPoint pos, int width, int height)
{
  width_menu = width;
  height_menu = height;
//  std::cout << width_menu << " " << height_menu << std::endl;
  QWidget::setGeometry(pos.x(), pos.y(), width, height);
}

void UpperMenu::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void UpperMenu::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void UpperMenu::mouseReleaseEvent(QMouseEvent* event)
{
  if(event->pos() != mouse_pos_clicked)
    return;
  if (point_in_rect(exit_butt(), event->pos()))
    graphic_controller->exit();
}

void UpperMenu::draw()
{
  QPainter qp(this);

  QPixmap pixmap{":/Graphics/image/menu/exit.png"};
  QRectF source{0., 0., 100., 100.};
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

bool UpperMenu::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
