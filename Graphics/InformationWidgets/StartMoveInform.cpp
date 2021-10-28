#include "StartMoveInform.h"
#include <iostream>

StartMoveInform::StartMoveInform(IGameForWidget* game, QString _string, QPoint _point)
  :QWidget{game->window()}, game_controller{game}, string{_string}, point{_point}
{
  setFocusPolicy(Qt::TabFocus);
}

void StartMoveInform::set_geometry(QPoint pos, Size size)
{
  QWidget::setGeometry(pos.x(), pos.y(), size.width, size.height);
}

void StartMoveInform::paintEvent(QPaintEvent* event)
{
  draw();
}

void StartMoveInform::mousePressEvent(QMouseEvent *event)
{
  mouse_pos_clicked = event->pos();
}

void StartMoveInform::mouseReleaseEvent(QMouseEvent *event)
{
  QPoint mouse_move = event->pos() - mouse_pos_clicked;
  if(abs(mouse_move.x()) > 5 or abs(mouse_move.y()) > 5)
    return;
  if(point_in_rect(rect_butt(), event->pos()))
    game_controller->start_move();
}

void StartMoveInform::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Enter-1 || event->key() == Qt::Key_Enter)
    game_controller->start_move();
}

void StartMoveInform::draw()
{
  QPainter qp(this);
  qp.setPen(QPen{Qt::white, 2});

  QFont font("");
  font.setPixelSize(height()/5);
  qp.setFont(font);
  qp.drawText(QRect{0, 0, width(), height() - rect_butt().height() - indentation_butt()},
              Qt::AlignCenter, string);

  QFont font2("");
  font2.setPixelSize(height()/20);
  qp.setFont(font2);
  qp.drawRect(rect_butt());
  qp.drawText(rect_butt(), Qt::AlignCenter, "Ок");
}


QRect StartMoveInform::rect_butt() const
{
  Size size_butt{width()/8, height()/10};
  return QRect{width()/2 - size_butt.width/2, height() - size_butt.height - indentation_butt(),
        size_butt.width, size_butt.height};
}

int StartMoveInform::indentation_butt() const
{
  return height()/20;
}

bool StartMoveInform::point_in_rect(QRectF rect, QPoint point)
{
  if (point.x() >= rect.topLeft().x() && point.x() < rect.bottomRight().x())
    if (point.y() >= rect.topLeft().y() && point.y() <= rect.bottomRight().y())
      return true;
  return false;
}
