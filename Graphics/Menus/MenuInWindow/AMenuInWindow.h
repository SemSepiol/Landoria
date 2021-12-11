#ifndef AMENUINWINDOW_H
#define AMENUINWINDOW_H

#include <QMouseEvent>
#include <QWidget>

#include "../../GraphicsController/IMenuGraphicsController.h"


class AMenuInWindow : public QWidget
{
public:
  AMenuInWindow(IMenuInWindowGraphicsController* graphics_controller);

  virtual void set_geometry(QPoint pos, Size size);

protected:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  virtual void draw() = 0;
  virtual void click(QPoint pos) = 0;

  bool point_in_rect(QRectF rect, QPoint point);

  int width_menu;
  int height_menu;
  IMenuInWindowGraphicsController* graphics_controller;

  QPoint mouse_pos_clicked;
};

#endif // AMENUINWINDOW_H
