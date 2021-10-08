#ifndef MENUTOWN_H
#define MENUTOWN_H

#include <QMouseEvent>
#include <QWidget>

#include "../../Controllers/IPlayer.h"
#include "../GraphicsController/IGraphicsController.h"
#include "../Buildings/Town.h"

class MenuTown : public QWidget
{
public:
  MenuTown(ITownMenuGraphicsController* graphics_controller, class Town* town);\
  void set_geometry(QPoint pos, Size size);
private:
  virtual void paintEvent(QPaintEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override {Q_UNUSED(event)}
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  void draw();
  IMenuTownPlayer* player();
  void click(QPoint pos);
  QRectF rect_butt_exit();
  bool point_in_rect(QRectF rect, QPoint point);

  ITownMenuGraphicsController* graphics_controller;
  class Town* town;
  QPoint mouse_pos_clicked;
};

#endif // MENUTOWN_H
