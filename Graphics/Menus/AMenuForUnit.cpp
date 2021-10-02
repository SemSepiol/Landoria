#include "AMenuForUnit.h"

AMenuForUnit::AMenuForUnit(QWidget* win, IGraphicsControllerMenuForUnit* _graphics_controller, class Unit* _unit)
  :QWidget(win), graphics_controller{_graphics_controller}, unit{_unit}
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
  mouse_pos_clicked = event->pos();
}

void AMenuForUnit::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
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
  graphics_controller->menu_unit_event(unit, what_butt(num_butt));
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
