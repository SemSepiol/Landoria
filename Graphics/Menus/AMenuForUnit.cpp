#include "AMenuForUnit.h"
#include <iostream>

AMenuForUnit::AMenuForUnit(QWidget* _win, IGraphicsControllerMenuForUnit* _graphics_controller,
                           class Unit* _unit, Cell* _cell)
  :QWidget(_win), graphics_controller{_graphics_controller}, unit{_unit}, cell{_cell}, win{_win}
{}

void AMenuForUnit::set_geometry(QPoint pos, int _side_square)
{
  pos_menu = pos;
  side_square = _side_square;
  QWidget::setGeometry(pos.x(), pos.y(), side_square, side_square * int(buttons.size()));
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

  for(size_t i{0}; i < buttons.size(); ++i)
    if(point_in_rect(rect_butt(i), event->pos()))
    {
      click_butt(i);
      break;
    }
}

int AMenuForUnit::count_button() const
{
  return int(buttons.size());
}

void AMenuForUnit::draw()
{
  QList<QRectF> list;
  for(size_t i{0}; i < buttons.size(); ++i)
  {
    list.append(rect_butt(i));
    draw_butt(i);
  }
  QPainter qp(this);
  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  qp.drawRects(list);
}

void AMenuForUnit::click_butt(size_t num_butt)
{
  if(buttons[num_butt].event->event == Events::Move)
  {
    graphics_controller->menu_unit_event(unit, buttons[num_butt].event->copy());
    has_move_event = !has_move_event;
    return;
  }

  if(has_move_event)
  {
    has_move_event = false;
    graphics_controller->menu_unit_event(unit, new MoveEvent{0,0});
  }

  if (buttons[num_butt].is_enable)
    graphics_controller->menu_unit_event(unit, buttons[num_butt].event->copy());
}

void AMenuForUnit::draw_butt(size_t num_butt)
{
  QPainter qp(this);
  QRectF source = FactoryPixmap().size_picture_content();
  QPixmap pixmap = FactoryPixmap().create_pixmap_for_butt_menu(buttons[num_butt].event->copy());

  qp.drawPixmap(rect_butt(num_butt), pixmap, source);
  if(!buttons[num_butt].is_enable)
    qp.fillRect(rect_butt(num_butt), QBrush(QColor(0, 0, 0, 100)));
}


bool AMenuForUnit::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}

QRectF AMenuForUnit::rect_butt(size_t i)
{
  return QRectF{0., int(i)*side_square*1., side_square*1., side_square*1.};
}
