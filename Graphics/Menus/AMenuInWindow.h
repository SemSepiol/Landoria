#ifndef AMENUINWINDOW_H
#define AMENUINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include "../GraphicsController/IGraphicsControllerFor.h"

class AMenuInWindow : public QWidget
{
public:
  AMenuInWindow(IMenuInWindowGraphicsController* graphics_controller);
  virtual void set_geometry(QPoint pos, Size size);
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void draw() = 0;
  virtual void click(QPoint pos) = 0;

protected:
  bool point_in_rect(QRectF rect, QPoint point);

  int width_menu;
  int height_menu;
  IMenuInWindowGraphicsController* graphics_controller;

  QPoint mouse_pos_clicked;
};

#endif // AMENUINWINDOW_H
