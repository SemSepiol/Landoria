#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <memory>

#include <QWidget>
#include <QPoint>
#include <QResizeEvent>
#include <QPalette>
#include "../Controller/IGame.h"

class GameWindow : public QWidget
{
  const QPoint _p_win = QPoint{0,0};
public:
  GameWindow(IGameForWindow* game);

  void show();
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void resizeEvent(QResizeEvent *event) override;
private:
  IGameForWindow* game_controller;

  QPoint pos_mouse{-1, -1};
  bool mouse_is_moved = false;
};

#endif // GAME_WINDOW_H
