#include "MenuTypeMap.h"

MenuTypeMap::MenuTypeMap(IMenuInWindowGraphicsController* _graphics_controller, IMap* _map)
  : QWidget{_graphics_controller->window()}, graphics_controller{_graphics_controller}, map{_map}
{
  QWidget::setMouseTracking(true);
}

void MenuTypeMap::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

void MenuTypeMap::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void MenuTypeMap::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void MenuTypeMap::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}


void MenuTypeMap::draw()
{
  QPainter qp(this);
  qp.setPen(QPen(Qt::white, 2));
  QPoint p1;
  QPoint p2;

  qp.drawText(text_overlay(), Qt::AlignBottom, "Активное наложение:");
  qp.fillRect(wid_overlay(), QBrush(Qt::gray));
  qp.drawRect(wid_overlay());
  qp.drawText(wid_overlay(), Qt::AlignCenter, "fff");
  p1 = (wid_overlay().topRight() + wid_overlay().bottomRight())/2;
  p2 = wid_overlay().bottomRight() - QPoint{wid_overlay().height()/2, 0};
  qp.drawLine(p1, p2);

  qp.drawText(text_icons(), Qt::AlignBottom, "Отображение значков:");
  qp.fillRect(wid_icons(), QBrush(Qt::gray));
  qp.drawRect(wid_icons());
  qp.drawText(wid_icons(), Qt::AlignCenter, "fff");
  p1 = (wid_icons().topRight() + wid_icons().bottomRight())/2;
  p2 = wid_icons().bottomRight() - QPoint{wid_icons().height()/2, 0};
  qp.drawLine(p1, p2);

  qp.drawText(text_notvisible(), Qt::AlignVCenter, "Туман войны");
  QRect rect_notv = wid_notvisible();
  qp.drawEllipse(rect_notv.center(), rad_wid_notvisible(), rad_wid_notvisible());

  qp.drawText(text_other_landscapes(), Qt::AlignVCenter, "Особенности");
  QRect rect_ol = wid_other_landscapes();
  qp.drawEllipse(rect_ol.center(), rad_wid_other_landscapes(), rad_wid_other_landscapes());
}

void MenuTypeMap::click(QPoint pos)
{

}

QRect MenuTypeMap::text_overlay() const
{
  return QRect{width()/10, 0,  width()*8/10, height()/7};
}

QRect MenuTypeMap::wid_overlay() const
{
  return QRect{width()/10, height()/6,  width()*8/10, height()/7};
}

QRect MenuTypeMap::text_icons() const
{
  return QRect{width()/10, 2*height()/6, width()*8/10, height()/7};
}

QRect MenuTypeMap::wid_icons() const
{
  return QRect{width()/10, 3*height()/6, width()*8/10, height()/7};
}

QRect MenuTypeMap::text_notvisible() const
{ 
  return QRect{width()/10, 4*height()/6, width()*3/4, height()/6};
}

QRect MenuTypeMap::wid_notvisible() const
{
  return QRect{width()*3/4, 4*height()/6, width()/4, height()/6};
}

int MenuTypeMap::rad_wid_notvisible() const
{
  return wid_notvisible().width()/6;
}

QRect MenuTypeMap::text_other_landscapes() const
{
  return QRect{width()/10, 5*height()/6, width()*3/4, height()/6};
}

QRect MenuTypeMap::wid_other_landscapes() const
{
  return QRect{width()*3/4, 5*height()/6, width()/4, height()/6};
}

int MenuTypeMap::rad_wid_other_landscapes() const
{
  return wid_other_landscapes().width()/6;
}

