#include "MenuBuildTown.h"

MenuBuildTown::MenuBuildTown(IMenuTown* _menu_town)
  :QWidget{_menu_town->window()}, menu_town{_menu_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void MenuBuildTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

void MenuBuildTown::paintEvent(QPaintEvent* event)
{
  draw();
}

void MenuBuildTown::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuBuildTown::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
}

void MenuBuildTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));
}

bool MenuBuildTown::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
