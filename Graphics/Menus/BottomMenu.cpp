#include "BottomMenu.h"

BottomMenu::BottomMenu(IGraphicsControllerForMenuInWindow* _graphic_controller)
  : AMenuInWindow(_graphic_controller)
{}

void BottomMenu::draw()
{
  QPainter qp(this);

  QPixmap pixmap = FactoryPixmap().create_pixmap_for_minimap();
  QRectF source = FactoryPixmap().size_picture_content();
  qp.drawPixmap(show_minimap_butt(), pixmap, source);

  QPen pen{Qt::white, 2, Qt::SolidLine};
  qp.setPen(pen);
  QPoint p1 = QPoint{0, 0};
  QPoint p2 = QPoint{width_menu, 0};
  qp.drawLine(p1, p2);
}

QRect BottomMenu::show_minimap_butt() const
{
  QPoint topleft = QPoint{width_menu - height_menu, 0};
  QPoint bottomright = QPoint{width_menu, height_menu};
  return QRect{topleft, bottomright};
}

void BottomMenu::click(QPoint pos)
{
  if (point_in_rect(show_minimap_butt(), pos))
    graphic_controller->show_minimap();
}
