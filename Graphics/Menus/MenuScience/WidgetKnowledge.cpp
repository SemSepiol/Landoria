#include "WidgetKnowledge.h"
#include <iostream>

WidgetKnowledge::WidgetKnowledge(IMenuInWindowGraphicsController* _graphics_controller,
                Knowledge* _knowledge, PlayerScience* _player_sience)
  :QWidget{_graphics_controller->window()}, graphics_controller{_graphics_controller},
    knowledge{_knowledge}, player_sience{_player_sience}
{}


void WidgetKnowledge::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

void WidgetKnowledge::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  draw();
}

void WidgetKnowledge::mousePressEvent(QMouseEvent* event)
{
  mouse_pos_clicked = event->pos();
}

void WidgetKnowledge::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  click(event->pos());
}

void WidgetKnowledge::draw()
{
  QPainter qp(this);

  qp.setBrush(QBrush(QColor(Qt::red)));
  qp.drawRect(QRect{0, 0, width(), height()});
}

void WidgetKnowledge::click(QPoint pos)
{
  std::cout << "science" << std::endl;
}
