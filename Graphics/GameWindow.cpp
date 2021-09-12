#include "GameWindow.h"


GameWindow::GameWindow(IGame* game)
  : QWidget(), game_controller{game}
{
//  QWidget::showFullScreen();
  QWidget::resize(width_win, height_win);
  QWidget::move(p_win);
//  map->draw(std::unique_ptr<IGame>{this});
}

GameWindow::~GameWindow(){
  game_controller.~unique_ptr();
}

int GameWindow::height_window(){
  return height_win;
}

int GameWindow::width_window(){
  return width_win;
}

QPoint GameWindow::center_window(){
  return QPoint{width_win/2, height_win/2};
}
