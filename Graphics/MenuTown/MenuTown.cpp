#include "MenuTown.h"

MenuTown::MenuTown(ITownMenuGraphicsController* _graphics_controller, class Town* _town)
  :QWidget{_graphics_controller->window()}, graphics_controller{_graphics_controller}, town{_town}
{
  QWidget::setAttribute( Qt::WA_TranslucentBackground, true );
}

void MenuTown::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

void MenuTown::paintEvent(QPaintEvent* event)
{
  draw();
}

void MenuTown::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuTown::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;

  if(point_in_rect(rect_butt_exit(), event->pos()))
    graphics_controller->delete_townmenu();
}

void MenuTown::draw()
{
  QPainter qp(this);
  QRect rect{0, 0, width(), height()};
  qp.fillRect(rect, QBrush(QColor(0, 0, 0, 200)));

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_exit();
  QRectF source = FactoryPixmap().size_picture_content();
  qp.drawPixmap(rect_butt_exit(), pixmap, source);
}

IMenuTownPlayer* MenuTown::player()
{
  return graphics_controller->player();
}

QRectF MenuTown::rect_butt_exit()
{
  Size butt = {100, 100};
  return QRectF{(width() - butt.width)*1., (height() - butt.height)*1.,
        butt.width*1., butt.height*1.};
}

bool MenuTown::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
