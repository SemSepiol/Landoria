#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(IGame* game)
  : QWidget(), game_controller{game}
{}

GameWindow::~GameWindow(){
}

void GameWindow::show()
{
  //  QWidget::showFullScreen();
  QWidget::setFixedSize(game_controller->width_win(), game_controller->height_win());
  QWidget::move(_p_win);
  QWidget::show();
}

void GameWindow::paintEvent(QPaintEvent* e)
{
  game_controller->draw_map();
}
