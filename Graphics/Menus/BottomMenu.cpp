#include "BottomMenu.h"

BottomMenu::BottomMenu(IGraphicsControllerForMenuInWindow* _graphic_controller)
  : AMenuInWindow(_graphic_controller)
{}

void BottomMenu::mouseMoveEvent(QMouseEvent *event)
{
  if(event->pos().y() > height_menu - 5)
    graphics_controller->move_map({0, -50});
}

void BottomMenu::draw()
{
  QPainter qp(this);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_minimap();
  QRectF source = FactoryPixmap().size_picture_content();
  qp.drawPixmap(show_minimap_butt(), pixmap, source);

  QPixmap pixmap2 = FactoryPixmap().create_pixmap_for_nextmotion();
  qp.drawPixmap(next_move_butt(), pixmap2, source);

  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QPoint p1 = QPoint{0, 0};
  QPoint p2 = QPoint{width_menu, 0};
  qp.drawLine(p1, p2);
}



void BottomMenu::click(QPoint pos)
{
  if (point_in_rect(show_minimap_butt(), pos))
    graphics_controller->show_minimap();
}

QRect BottomMenu::show_minimap_butt() const
{
  QPoint topleft = QPoint{width_menu - 2*height_menu, 0};
  QPoint bottomright = QPoint{width_menu - height_menu, height_menu};
  return QRect{topleft, bottomright};
}

QRect BottomMenu::next_move_butt() const
{
  QPoint topleft = QPoint{width_menu - height_menu, 0};
  QPoint bottomright = QPoint{width_menu, height_menu};
  return QRect{topleft, bottomright};
}
