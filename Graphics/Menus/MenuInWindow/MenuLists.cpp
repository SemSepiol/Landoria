#include "MenuLists.h"

MenuLists::MenuLists(IMenuInWindowGraphicsController* graphics_controller)
  :AMenuInWindow(graphics_controller)
{}

void MenuLists::draw()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 2});
  qp.drawText(QRect{0, 0, width(), height()}, Qt::AlignCenter, QString("Меню науки"));
}

void MenuLists::click(QPoint pos)
{
  graphics_controller->open_menu_science();
}
