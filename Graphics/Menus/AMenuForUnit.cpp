#include "AMenuForUnit.h"

AMenuForUnit::AMenuForUnit(QWidget* win, IPlayerForMenu* _player, class Unit* _unit)
  :QWidget(win), player{_player}, unit{_unit}
{}

void AMenuForUnit::set_geometry(QPoint pos, int _side_square)
{
  side_square = _side_square;
  QWidget::setGeometry(pos.x(), pos.y(), side_square, side_square*count_button());
}

void AMenuForUnit::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event)
  draw();
}

void AMenuForUnit::mousePressEvent(QMouseEvent *event)
{
  mouse_click_pos = event->pos();
}

void AMenuForUnit::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->pos() != mouse_click_pos)
    return;

  for(int i{0}; i < count_button(); ++i)
    if(point_in_rect(rect_butt(i), event->pos()))
    {
      click_butt(i);
      break;
    }

}

void AMenuForUnit::draw()
{
  QPainter qp(this);
  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QList<QRectF> list;
  for(int i{0}; i < count_button(); ++i)
  {
    list.append(rect_butt(i));
    QRectF source{0., 0., 188., 188.};
    qp.drawPixmap(rect_butt(i), FactoryPixmap().create_pixmap_for_butt_menu(what_butt(i)), source);
  }
  qp.drawRects(list);
}

void AMenuForUnit::click_butt(int num_butt)
{
  player->menu_event(what_butt(num_butt), unit);
}

bool AMenuForUnit::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}

QRectF AMenuForUnit::rect_butt(int i)
{
  return QRectF{0., i*side_square*1., side_square*1., side_square*1.};
}
