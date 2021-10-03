#include "AMenuInWindow.h"

AMenuInWindow::AMenuInWindow(IGraphicsControllerForMenuInWindow* _graphics_controller)
  : QWidget{_graphics_controller->window()} ,graphics_controller{_graphics_controller}
{
  QWidget::setMouseTracking(true);
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
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
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
