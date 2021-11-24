#include "OpenMenuLists.h"

OpenMenuLists::OpenMenuLists(IMenuInWindowGraphicsController* graphics_controller)
  :AMenuInWindow(graphics_controller)
{}

void OpenMenuLists::draw()
{
  QPainter qp(this);
  QPixmap pixmap;
  if(is_menu_open)
    pixmap = FactoryPixmap().create_pixmap_for_up_in_queue();
  else
    pixmap = FactoryPixmap().create_pixmap_for_down_in_queue();

  QRectF source = FactoryPixmap().size_picture_content();
  QRect rect = QRect{0, 0, width(), height()};
  qp.drawPixmap(rect, pixmap, source);
  qp.setPen(QPen{Qt::white});
  qp.drawRect(rect);
}

void OpenMenuLists::click(QPoint pos)
{
  Q_UNUSED(pos)
  if(is_menu_open)
    graphics_controller->close_menu_lists();
  else
    graphics_controller->open_menu_lists();
  is_menu_open = !is_menu_open;
  update();
}
