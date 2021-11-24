#include "AWidgetTown.h"
#include <iostream>

AWidgetTown::AWidgetTown(QWidget* win, TypeWork _type_widget)
  :QWidget{win}, type_widget{_type_widget}
{}

void AWidgetTown::draw_butt()
{
  if(type_widget == InQueue)
  {
    QPainter qp(this);

    QPixmap pixmap = FactoryPixmap().create_pixmap_for_del_in_queue();
    QRectF source = FactoryPixmap().size_picture_content();
    qp.drawPixmap(rect_butt_del(), pixmap, source);

    if(num_from_queue() != 0)
    {
      pixmap = FactoryPixmap().create_pixmap_for_up_in_queue();
      source = FactoryPixmap().size_picture_content();
      qp.drawPixmap(rect_butt_up(), pixmap, source);
    }

    if(num_from_queue() + 1 != count_from_queue())
    {
      pixmap = FactoryPixmap().create_pixmap_for_down_in_queue();
      source = FactoryPixmap().size_picture_content();
      qp.drawPixmap(rect_butt_down(), pixmap, source);
    }
  }
}

void AWidgetTown::draw_enable()
{
  if(!enable && type_widget == Build)
  {
    QPainter qp(this);
    qp.fillRect(QRect(0,0, width(), height()), QBrush(QColor(0, 0, 0, 100)));
  }
}

QRect AWidgetTown::rect_butt_del()
{
  int side_butt = height()/2;
  return QRect{QPoint{width() - side_butt - height()/10, height()/4},
    QPoint{width() - height()/10, height()/4 + side_butt}};
}

bool AWidgetTown::point_in_rect(QRectF rect, QPoint point) const
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}

QRect AWidgetTown::rect_butt_up()
{
  int side_butt = height()/2;
  int a = side_butt;
  if(num_from_queue() + 1 != count_from_queue())
    a += side_butt;
  return QRect{QPoint{width() - a - side_butt - height()/10, height()/4},
    QPoint{width() - a - height()/10, height()/4 + side_butt}};
}

QRect AWidgetTown::rect_butt_down()
{
  int side_butt = height()/2;
  return QRect{QPoint{width() - 2*side_butt - height()/10, height()/4},
    QPoint{width() - side_butt - height()/10, height()/4 + side_butt}};
}

QRect AWidgetTown::rect_pic()
{
  return QRect{QPoint{0,0}, QPoint{height(), height()}};
}
