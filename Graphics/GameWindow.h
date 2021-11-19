#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <memory>

#include <QPalette>
#include <QPoint>
#include <QResizeEvent>
#include <QWidget>

#include "GraphicsController/IWindowGraphicsController.h"
#include "MenuTown/InformWidget.h"


class GameWindow : public QWidget
{
  const QPoint _p_win = QPoint{0,0};
public:
  GameWindow(IWindowGraphicsController* game);

  void show();
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void keyPressEvent(QKeyEvent *event) override;

  void do_inform_widget(std::vector<std::pair<QString, QColor>> text);
  void del_inform_widget();
private:
  void control_mouse_at_edge(QPoint event_pos);

  IWindowGraphicsController* graphics_controller;

  QPoint pos_mouse{-1, -1};
  QPoint pos_mouse_clicked{-1, -1};
  bool mouse_is_clicked = false;
  Qt::MouseButton mouse_button_cliked = Qt::NoButton;

  std::unique_ptr<InformWidget> inform_widget;
};

#endif // GAME_WINDOW_H
