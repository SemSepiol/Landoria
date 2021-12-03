#include "StartMenu.h"

StartMenu::StartMenu(IMenuStartGraphicsController* _graphics_controller)
  :QWidget(_graphics_controller->window()), graphics_controller{_graphics_controller}
{}

void StartMenu::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

void StartMenu::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void StartMenu::mousePressEvent(QMouseEvent* event)
{
  mouse_pos_clicked = event->pos();
}

void StartMenu::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}

void StartMenu::draw()
{

}

void StartMenu::click(QPoint pos)
{
  graphics_controller->start_game();
}
