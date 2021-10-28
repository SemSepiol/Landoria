#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(IWindowGraphicsController* game)
  : QWidget(), graphics_controller{game}, inform_widget{new InformWidget{this}}
{
  //  setWindowState(windowState() ^ Qt::WindowFullScreen);
  setStyleSheet("background-color:black;");
  QWidget::setMouseTracking(true);
  setFocusPolicy(Qt::TabFocus);
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
  graphics_controller->draw_elements();
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
  inform_widget->hide();
  control_mouse_at_edge(event->pos());
  graphics_controller->move_mouse(event->pos());
  if(mouse_is_clicked and mouse_button_cliked == Qt::LeftButton){
    graphics_controller->move_map(event->pos() - pos_mouse);
  }
  pos_mouse = event->pos();

}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
  if(event->button() == Qt::RightButton)
  {
    mouse_button_cliked = Qt::RightButton;
    graphics_controller->start_check_move_unit();
  }
  if(event->button() == Qt::LeftButton)
  {
    mouse_button_cliked = Qt::LeftButton;
  }
  pos_mouse = event->pos();
  mouse_is_clicked = true;
  pos_mouse_clicked = event->pos();
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
  if(mouse_button_cliked == Qt::RightButton)
  {
    graphics_controller->stop_check_move_unit(event->pos());
  }
  else
  {
    QPoint move_mouse = event->pos() - pos_mouse_clicked;
    if(abs(move_mouse.x()) < 5 and abs(move_mouse.y()) < 5)
      graphics_controller->click(event->pos());
  }
  mouse_is_clicked = false;
}

void GameWindow::wheelEvent(QWheelEvent* event)
{
  int angle_delta = event->angleDelta().y();
  double coefficient = 1. + angle_delta*1./1000;
  graphics_controller->resize_map(coefficient, event->position().toPoint());
}

void GameWindow::do_inform_widget(QString text)
{
  std::string str = text.toStdString();
  QPoint globalCursorPos = QCursor::pos();
//  inform_widget->move(globalCursorPos - QPoint{width()/20, 0} - inform_widget->pos());
//  inform_widget->set_set_geometry(globalCursorPos - QPoint{width()/20, 0}, {width()/20, count_str*height()/70});
  inform_widget->set_set_geometry(globalCursorPos - QPoint{width()/20, 0}, {width()/20, inform_widget->height()});
  inform_widget->set_text(text);
  inform_widget->show();
//  inform_widget->update();
  inform_widget->raise();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Enter-1 || event->key() == Qt::Key_Enter)
    graphics_controller->press_enter();
}

void GameWindow::del_inform_widget()
{
  inform_widget->hide();
}

void GameWindow::control_mouse_at_edge(QPoint event_pos)
{
  if(event_pos.x() < 5 && pos_mouse.x() < 5)
    graphics_controller->move_map({50, 0});
  if(event_pos.x() > width()-5 && pos_mouse.x() > width()-5)
    graphics_controller->move_map({-50, 0});
  if(event_pos.y() < 5)
    graphics_controller->move_map({0, 50});
  if(event_pos.y() > height() - 5)
    graphics_controller->move_map({0, -50});
}
