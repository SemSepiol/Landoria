#include "AMenuInWindow.h"

AMenuInWindow::AMenuInWindow(IGraphicsControllerForMenuInWindow* graphic_controller)
  : QWidget{graphic_controller->window()} ,graphic_controller{graphic_controller}
{

}

void AMenuInWindow::set_geometry(QPoint pos, int width, int height)
{
  width_menu = width;
  height_menu = height;
  QWidget::setGeometry(pos.x(), pos.y(), width, height);
}


void AMenuInWindow::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void AMenuInWindow::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void AMenuInWindow::mouseReleaseEvent(QMouseEvent* event)
{
  if(event->pos() != mouse_pos_clicked)
    return;
  click(event->pos());

}

bool AMenuInWindow::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
