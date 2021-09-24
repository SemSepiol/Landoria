#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(IGameForWindow* game)
  : QWidget(), game_controller{game}
{
  setStyleSheet("background-color:black;");
}

void GameWindow::show()
{
//  QWidget::showFullScreen();
  QWidget::setFixedSize(game_controller->width_win(), game_controller->height_win());
//  QWidget::resize(game_controller->width_win(), game_controller->height_win());
  QWidget::move(_p_win);
  QWidget::show();
}

void GameWindow::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  game_controller->draw_map();
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
  mouse_is_moved = true;
  game_controller->move_map(event->pos() - pos_mouse);
  pos_mouse = event->pos();
//  std::cout << event->pos().x() << "::" << event->pos().y() << std::endl;
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
  pos_mouse = event->pos();
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
  if(!mouse_is_moved)
    game_controller->click(event->pos());
  mouse_is_moved = false;
}

void GameWindow::wheelEvent(QWheelEvent* event)
{
  int angle_delta = event->angleDelta().y();
  double coefficient = 1. + angle_delta*1./1000;
//  std::cout << coefficient << std::endl;
  game_controller->resize_map(coefficient);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
  game_controller->resize_win(event->size());
}
