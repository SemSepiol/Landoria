#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(IGraphicsControllerForWindow* game)
  : QWidget(), graphics_controller{game}
{
//  setWindowState(windowState() ^ Qt::WindowFullScreen);
  setStyleSheet("background-color:black;");
  QWidget::setMouseTracking(true);
}

void GameWindow::show()
{
  QWidget::showFullScreen();
//  QWidget::setFixedSize(graphics_controller->width_win(), graphics_controller->height_win());
//  QWidget::resize(game_controller->width_win(), game_controller->height_win());
//  QWidget::move(_p_win);
//  QWidget::show();
}

void GameWindow::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event)
  graphics_controller->draw_map();
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
  if(mouse_is_clicked){
    graphics_controller->move_map(event->pos() - pos_mouse);
    pos_mouse = event->pos();
  }
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
  pos_mouse = event->pos();
  mouse_is_clicked = true;
  pos_mouse_clicked = event->pos();
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
  QPoint move_mouse = event->pos() - pos_mouse_clicked;
  if(abs(move_mouse.x()) < 5 and abs(move_mouse.y()) < 5)
    graphics_controller->click(event->pos());
  mouse_is_clicked = false;
}

void GameWindow::wheelEvent(QWheelEvent* event)
{
  int angle_delta = event->angleDelta().y();
  double coefficient = 1. + angle_delta*1./1000;
  graphics_controller->resize_map(coefficient);
}
